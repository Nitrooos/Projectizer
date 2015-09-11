#include "CNewProjectWindow.hpp"
#include "ui_NewProjectWindow.h"

#include "src/new_projects/project_type_item/CProjectTypeItem.hpp"
#include "src/file_finder/CProjectTemplateFileFinder.hpp"
#include "src/CConstants.hpp"

#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QKeyEvent>

CNewProjectWindow::CNewProjectWindow(const QString &directory, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::NewProjectWindow),  _directory(directory)
{
    ui->setupUi(this);
    ui->treeView->header()->setVisible(false);

    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->createButton, SIGNAL(clicked()), this, SLOT(createNewProject()));
    connect(ui->treeView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(buildTemplateOptions()));

    /* DOKLEJONE */
    auto standardModel = new QStandardItemModel;
    QStandardItem *item = standardModel->invisibleRootItem();

    CProjectTemplateFileFinder finder(
        CConstant::getProjectizerMainFolder() + CConstant::getTemplatesFolder(),
        item
    );
    finder.findTemplateFilesBFS();

    ui->treeView->setModel(standardModel);
    ui->treeView->expandAll();
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
    QModelIndex selected_index = selected.indexes().first();
}
