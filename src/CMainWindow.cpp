#include "CMainWindow.hpp"
#include "CConstants.hpp"
#include "model/CProjectModel.hpp"
#include "file_finder/CXMLFileFinder.hpp"
#include "parser/CProjectXmlFileReader.hpp"
#include "ui_MainWindow.h"

#include <QKeyEvent>
#include <QDesktopWidget>

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(close()));

    this->hideRemoveAndConfigureButtons();
    this->centerWindow();
    this->fillTableViewWithSavedProjectsData();
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

// fill and set model for table view (<project name, technology> row)
void CMainWindow::fillTableViewWithSavedProjectsData() {
    QStringList saved_projects_files = CXMLFileFinder::getSavedProjectsXMLFiles(
                CConstant::getProjectizerMainFolder() + CConstant::getSavedProjectsFolder());

    ProjectInfoList saved_projects_info_list;
    foreach (const QString &file_name, saved_projects_files) {
        CProjectXmlFileReader reader(file_name);
        reader.parse();
        SProjectInfo saved_project_info = reader.getParsedInformations();

        saved_projects_info_list.push_back(ProjectRowInfo{saved_project_info._name, saved_project_info._type});
    }

    ui->tableView->setModel(new CProjectModel(saved_projects_info_list, this));
}
