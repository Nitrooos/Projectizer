#include "CSavedProjectsTableView.hpp"
#include "src/model/CProjectModel.hpp"
#include "src/file_finder/CXMLFileFinder.hpp"
#include "src/CConstants.hpp"
#include "src/parser/CProjectXmlFileReader.hpp"

#include <QMessageBox>
#include <QHeaderView>
#include <QStringList>

CSavedProjectsTableView::CSavedProjectsTableView(QWidget *parent) : QTableView(parent), _model(nullptr) {
    this->setup();
}

void CSavedProjectsTableView::setup() {
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->fillWithSavedProjectsData();

    // porawki wizualne (ukrycie siatki, odpowiednie rozmiary kolumn, zablokowanie rozszerzania kolumn)
    this->setColumnWidth(0, 200);
    this->setColumnWidth(1, 149);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onDoubleClick(QModelIndex)));

    this->show();
}

// fill and set model for table view (<project name, technology> row)
void CSavedProjectsTableView::fillWithSavedProjectsData() {
    QStringList saved_projects_files = CXMLFileFinder::getSavedProjectsXMLFiles(
        CConstant::getProjectizerMainFolder() + CConstant::getSavedProjectsFolder()
    );

    QList<SProjectInfo> saved_projects_info_list;
    foreach (const QString &file_name, saved_projects_files) {
        CProjectXmlFileReader reader(file_name);
        reader.parse();
        SProjectInfo saved_project_info = reader.getParsedInformations();

        saved_projects_info_list.push_back(saved_project_info);
    }

    this->_model = new CProjectModel(saved_projects_info_list, this);
    this->setModel(_model);
}

#include <iostream>
void CSavedProjectsTableView::onDoubleClick(QModelIndex index) {
    Q_UNUSED(index);

    SProjectInfo saved_project_info = this->_model->getList().at(index.row());

    QProcess script_process;

    QObject::connect(&script_process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(onProcessError(QProcess::ProcessError)));

    script_process.setWorkingDirectory(saved_project_info._location);
    script_process.start(saved_project_info._run_script);

    script_process.waitForFinished();
}

void CSavedProjectsTableView::onProcessError(QProcess::ProcessError error) {
    QMessageBox box;
    switch (error) {
        case QProcess::FailedToStart:
            box.setText("The process failed to start. Either the invoked program is missing, or you may have insufficient permissions to invoke the program.");
            break;
        case QProcess::Crashed:
            box.setText("The process crashed some time after starting successfully.");
            break;
        case QProcess::UnknownError:
        default:
            box.setText("An unknown error occurred.");
            break;
    }

    box.exec();
}
