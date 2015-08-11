#include "CMainWindow.hpp"
#include "CConstants.hpp"
#include "model/CProjectModel.hpp"
#include "file_finder/CXMLFileFinder.hpp"
#include "ui_MainWindow.h"

#include <QKeyEvent>
#include <QDesktopWidget>

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
    this->hideRemoveAndConfigureButtons();
    this->centerWindow();
    this->fillTableViewWithSavedProjectsData();

    //ProjectInfo info;
    //info.push_back(ProjectRowInfo{"name", {"tech1", "tech2"}});
    //ui->tableView->setModel(new CProjectModel(info, this));
}

CMainWindow::~CMainWindow() {
    delete ui;
}

// ESC should close application (fatser testing), no other changes
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

void CMainWindow::hideRemoveAndConfigureButtons() const {
    ui->removeButton->hide();
    ui->configureButton->hide();
}

#include <iostream>
void CMainWindow::fillTableViewWithSavedProjectsData() {
    QStringList saved_project_files = CXMLFileFinder::getSavedProjectsXMLFiles(
                CConstant::getProjectizerMainFolder() + CConstant::getSavedProjectsFolder());
    std::cout << saved_project_files.join(", ").toStdString() << "\n";
}
