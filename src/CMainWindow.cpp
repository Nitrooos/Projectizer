#include "CMainWindow.hpp"
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

    connect(ui->tableView, SIGNAL(scriptRunSuccessfully()), this, SLOT(close()));
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
