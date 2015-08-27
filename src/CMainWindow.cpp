#include "CMainWindow.hpp"
#include "dialog/CConfigureProjectDialog.hpp"
#include "ui_MainWindow.h"

#include <QKeyEvent>
#include <QDesktopWidget>

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);

    this->setRemoveAndConfigureButtonsVisibility(false);
    this->centerWindow();

    connect(ui->tableView, SIGNAL(scriptRunSuccessfully()), this, SLOT(close()));
    connect(ui->tableView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(handleTableViewSelectionChange()));
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

#include <iostream>
void CMainWindow::runConfigureProjectDialog() {
    auto *dialog = new CConfigureProjectDialog(this);

    if (dialog->exec() == QDialog::Accepted) {
        // pobierz nazwę nowego skryptu uruchomieniowego, zapisz w modelu i od razu w pliku
        std::cout << dialog->getNewRunScriptFile().toStdString() << "\n";
    }

    delete dialog;
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
