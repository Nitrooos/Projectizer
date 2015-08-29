#include "CConfigureProjectDialog.hpp"
#include "src/model/CProjectModel.hpp"
#include "src/parser/CProjectXmlFileWriter.hpp"
#include "ui_ConfigureProjectDialog.h"

#include <QFileDialog>
#include <QMessageBox>

CConfigureProjectDialog::CConfigureProjectDialog(QWidget *parent, SProjectInfo &project_info) :
    QDialog(parent), ui(new Ui::ConfigureProjectDialog), _edited_project_info(project_info)
{
    ui->setupUi(this);
    ui->newRunScriptFileLabel->setText(_edited_project_info._run_script);

    connect(ui->browseRunScriptFileButton, SIGNAL(clicked()), this, SLOT(browseFileAsRunScript()));
}

CConfigureProjectDialog::~CConfigureProjectDialog() {
    delete ui;
}

/*
 * Private slots
 */

void CConfigureProjectDialog::accept() {
    // pobierz nazwę nowego skryptu uruchomieniowego, zapisz w modelu
    _edited_project_info._run_script = ui->newRunScriptFileLabel->text();
    // i od razu w pliku
    CProjectXmlFileWriter writer(_edited_project_info);
    if (!writer.save()) {
        QMessageBox box;
        box.setText("Cannot update xml file associated with project. Does it still exist and you have write permissions?");
    }

    this->close();
    this->setResult(QDialog::Accepted);
}

void CConfigureProjectDialog::browseFileAsRunScript() {
    QFileDialog *file_dialog = new QFileDialog(this);
    ui->newRunScriptFileLabel->setText(file_dialog->getOpenFileName());
}
