#include "CSavedProjectsTableView.hpp"
#include "src/model/CProjectModel.hpp"
#include "src/file_finder/CXMLFileFinder.hpp"
#include "src/CConstants.hpp"
#include "src/parser/CProjectXmlFileReader.hpp"

#include <QProcess>
#include <QStringList>

CSavedProjectsTableView::CSavedProjectsTableView(QWidget *parent) : QTableView(parent), _model(nullptr) {
    this->setup();
}

void CSavedProjectsTableView::setup() {
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->fillWithSavedProjectsData();

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
    script_process.setWorkingDirectory(saved_project_info._location);
    script_process.start("/bin/bash " + saved_project_info._run_script);

    script_process.waitForFinished();
}
