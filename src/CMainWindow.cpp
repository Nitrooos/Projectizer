#include "CMainWindow.hpp"
#include "model/CProjectModel.hpp"
#include "ui_MainWindow.h"

#include <QDesktopWidget>

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
    this->hideRemoveAndConfigureButtons();
    this->centerWindow();

    ProjectInfo info;
    info.push_back(ProjectRowInfo{"name", {"tech1", "tech2"}});

    ui->tableView->setModel(new CProjectModel(info, this));
}

CMainWindow::~CMainWindow() {
    delete ui;
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
