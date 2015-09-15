#include "CNewProjectWindow.hpp"
#include "ui_NewProjectWindow.h"

#include "src/file_finder/CProjectTemplateFileFinder.hpp"
#include "src/new_projects/model/CProjectTypeItem.hpp"
#include "src/CConstants.hpp"

#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QKeyEvent>
#include <QLayout>
#include <QCheckBox>

CNewProjectWindow::CNewProjectWindow(const QString &directory, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::NewProjectWindow),  _directory(directory), _model(new CProjectTypeModel())
{
    ui->setupUi(this);
    ui->treeView->header()->setVisible(false);

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
    close();
}

#include <iostream>
void CNewProjectWindow::buildTemplateOptions(const QItemSelection &selected, const QItemSelection &deselected) {
    Q_UNUSED(deselected);

    CProjectTypeItem *selected_project_type = static_cast<CProjectTypeItem*>(selected.indexes().first().internalPointer());
    std::cout << selected_project_type->getProjectTypeInfo()._name.toStdString() << std::endl;

    QLayoutItem *item;
    while ((item = ui->optionsLayout->takeAt(0)) != 0) {
        delete item;
    }

    for (auto option : selected_project_type->getProjectTypeInfo()._options) {
        QHBoxLayout *rendered_layout = option->render();
        if (rendered_layout != nullptr) {
            std::cout << "OK" << std::endl;
            ui->optionsLayout->addLayout(rendered_layout);
        }
    }
}
