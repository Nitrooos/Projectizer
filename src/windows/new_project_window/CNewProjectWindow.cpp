#include "CNewProjectWindow.hpp"
#include "ui_NewProjectWindow.h"

#include "src/common/CScriptExecutor.hpp"
#include "src/file_finder/CProjectTemplateFileFinder.hpp"
#include "src/new_projects/model/CProjectTypeItem.hpp"
#include "src/CConstants.hpp"

#include <QTreeView>
#include <QKeyEvent>
#include <QLayout>

CNewProjectWindow::CNewProjectWindow(const QString &directory, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::NewProjectWindow),  _directory(directory), _model(new CProjectTypeModel()),
      _activeProjectItem(nullptr)
{
    ui->setupUi(this);
    ui->treeView->header()->setVisible(false);

    this->_layout_manager = new CLayoutManager(ui->layoutOptionsWidget, ui->optionsLayout);

    CProjectTemplateFileFinder finder(CConstant::getProjectizerMainFolder() + CConstant::getTemplatesFolder());
    finder.findTemplateFilesBFS(this->_model->getRootItem());

    ui->treeView->setModel(this->_model);
    ui->treeView->expandAll();

    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->createButton, SIGNAL(clicked()), this, SLOT(createNewProject()));
    connect(ui->treeView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(buildTemplateOptions(const QItemSelection &, const QItemSelection &)));
}

CNewProjectWindow::~CNewProjectWindow() {
    delete this->_layout_manager;
    delete this->_model;
}

/*
 * Private functions
 */

// ESC should close application (faster testing), no other changes
void CNewProjectWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Escape:
            close();
            break;
        default:
            QMainWindow::keyPressEvent(event);
    }
}

/*
 * Private slots
 */

void CNewProjectWindow::createNewProject() {
    if (this->_activeProjectItem == nullptr) {
        return;
    }

    QStringList params;
    for (auto o : this->_activeProjectItem->getProjectTypeInfo()._options) {
        params << o->value();
    }

    SProjectTypeInfo info = this->_activeProjectItem->getProjectTypeInfo();
    CScriptExecutor script(info._create_script_dir + "/create.sh", params, this->_directory);
    if (script.execute()) {
        close();
    }
}

void CNewProjectWindow::buildTemplateOptions(const QItemSelection &selected, const QItemSelection &deselected) {
    Q_UNUSED(deselected);

    // pobierz informacje o zaznaczonym typie projektu
    this->_activeProjectItem = static_cast<CProjectTypeItem*>(selected.indexes().first().internalPointer());

    this->_layout_manager->clearMainLayout();
    for (auto option : this->_activeProjectItem->getProjectTypeInfo()._options) {
        // dodawaj kolejne opcje (każda składa się z listy Widget'ów
        this->_layout_manager->addLayoutWithWidgets(option->render(ui->layoutOptionsWidget));
    }
}
