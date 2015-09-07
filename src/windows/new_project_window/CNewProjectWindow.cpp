#include "CNewProjectWindow.hpp"
#include "ui_NewProjectWindow.h"

#include "src/new_projects/project_type_item/CProjectTypeItem.hpp"

#include <QTreeView>
#include <QStandardItemModel>

CNewProjectWindow::CNewProjectWindow(const QString &directory, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::NewProjectWindow),  _directory(directory)
{
    ui->setupUi(this);

    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->createButton, SIGNAL(clicked()), this, SLOT(createNewProject()));

    /* DOKLEJONE */
    auto standardModel = new QStandardItemModel;

    QList<QStandardItem *> preparedRow = prepareRow("C++");
    QStandardItem *item = standardModel->invisibleRootItem();
    // adding a row to the invisible root item produces a root element
    item->appendRow(preparedRow);

    QList<QStandardItem *> secondRow = prepareRow("Games");
    // adding a row to an item starts a subtree
    preparedRow.first()->appendRow(secondRow);

    QList<QStandardItem *> thirdRow = prepareRow("SFML");
    secondRow.first()->appendRow(thirdRow);

    ui->treeView->setModel(standardModel);
    ui->treeView->expandAll();
}

QList<QStandardItem *> CNewProjectWindow::prepareRow(const QString &text) {
    SProjectTypeInfo info {text, {"test1", "test2", "test3"}, {nullptr}};
    QList<QStandardItem *> rowItems;
    rowItems << new CProjectTypeItem(info);
    return rowItems;
}

void CNewProjectWindow::createNewProject() {
    close();
}
