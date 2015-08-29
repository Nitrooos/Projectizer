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

SProjectInfo &CSavedProjectsTableView::getSelectedProjectInfo() {
    QModelIndexList selected = this->selectionModel()->selectedRows();
    return this->_model->getItem(selected.first().row());
}

CProjectModel *CSavedProjectsTableView::model() const {
    return this->_model;
}

/*
 * Public slots
 */

void CSavedProjectsTableView::runProjectScript(QModelIndex index) {
    QProcess script_process;
    QObject::connect(&script_process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(handleProcessError(QProcess::ProcessError)));

    SProjectInfo saved_project_info = this->_model->getList().at(index.row());
    script_process.setWorkingDirectory(saved_project_info._location);
    script_process.start(saved_project_info._run_script);

    if (script_process.waitForFinished()) {
        emit scriptRunSuccessfully();
    }
}

void CSavedProjectsTableView::handleProcessError(QProcess::ProcessError error) {
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

void CSavedProjectsTableView::removeSavedProjectXMLFile() {
    QModelIndexList selected_indexes = this->selectionModel()->selectedRows();
    if (selected_indexes.empty()) {
        return;
    }

    QModelIndex index = selected_indexes.first();
    QFile saved_project_xml_file(this->_model->getList().at(index.row())._project_xml_file);

    if (!saved_project_xml_file.remove()) {
        // jeśli nie udało się usunąć pliku...
        QMessageBox box;
        box.setText("Cannot remove specified project: Does its xml file still exist?");
    } else {
        // jeśli usunięto plik XML danego projetu
        this->_model->removeRow(index.row());
    }
}

/*
 * Private functions
 */

void CSavedProjectsTableView::setup() {
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->fillWithSavedProjectsData();

    // porawki wizualne (ukrycie siatki, odpowiednie rozmiary kolumn, zablokowanie rozszerzania kolumn)
    this->setColumnWidth(0, 200);
    this->setColumnWidth(1, 149);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(runProjectScript(QModelIndex)));

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

void CSavedProjectsTableView::keyPressEvent(QKeyEvent *event) {
    QModelIndexList selected_indexes_list = this->selectionModel()->selection().indexes();

    switch (event->key()) {
        case Qt::Key_Return:
            if (!selected_indexes_list.empty()) {
                this->runProjectScript(selected_indexes_list.first());
            }
            break;
        default:
            QTableView::keyPressEvent(event);
    }
}
