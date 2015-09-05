#include "CMainWindow.hpp"
#include "../configure_dialog/CConfigureProjectDialog.hpp"
#include "../new_project_dialog/CNewProjectWindow.hpp"
#include "ui_MainWindow.h"

#include <QKeyEvent>
#include <QDesktopWidget>

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
    ui->tableView->selectRow(0);

    this->centerWindow();

    connect(ui->tableView, SIGNAL(scriptRunSuccessfully()), this, SLOT(close()));
    connect(ui->tableView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(handleTableViewSelectionChange()));
    connect(ui->newProjectButton, SIGNAL(clicked()), this, SLOT(runNewProjectWindow()));
    connect(ui->removeButton, SIGNAL(clicked()), ui->tableView, SLOT(removeSavedProjectXMLFile()));
    connect(ui->configureButton, SIGNAL(clicked()), this, SLOT(runConfigureProjectDialog()));
}

CMainWindow::~CMainWindow() {
    delete ui;
}

/*
 * Public slots
 */

void CMainWindow::handleTableViewSelectionChange() {
    if (ui->tableView->selectionModel()->selectedRows().empty()) {
        this->setRemoveAndConfigureButtonsVisibility(false);
    } else {
        this->setRemoveAndConfigureButtonsVisibility(true);
    }
}

void CMainWindow::runConfigureProjectDialog() {
    SProjectInfo &selected_project_info = ui->tableView->getSelectedProjectInfo();

    auto *dialog = new CConfigureProjectDialog(this, selected_project_info);
    dialog->exec();

    delete dialog;
}

void CMainWindow::runNewProjectWindow() {
    auto *window = new CNewProjectWindow("", this);
    window->show();

    delete window;
}

/*
 * Private functions
 */

// ESC should close application (faster testing), no other changes
void CMainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Escape:
            close();
            break;
        default:
            QMainWindow::keyPressEvent(event);
    }
}

// set window position at center of screen
void CMainWindow::centerWindow() {
    int width  = this->frameGeometry().width(),
        height = this->frameGeometry().height();

    QDesktopWidget wid;
    int screenWidth = wid.screen()->width(),
        screenHeight = wid.screen()->height();

    this->setGeometry((screenWidth/2) - (width/2), (screenHeight/2) - (height/2), width, height);
}

void CMainWindow::setRemoveAndConfigureButtonsVisibility(bool visible) const {
    ui->removeButton->setVisible(visible);
    ui->configureButton->setVisible(visible);
}
