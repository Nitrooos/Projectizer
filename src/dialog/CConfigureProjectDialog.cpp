#include "CConfigureProjectDialog.hpp"
#include "ui_ConfigureProjectDialog.h"

#include <QFileDialog>

CConfigureProjectDialog::CConfigureProjectDialog(QWidget *parent, QString current_run_script_file) :
    QDialog(parent), ui(new Ui::ConfigureProjectDialog)
{
    ui->setupUi(this);
    ui->newRunScriptFileLabel->setText(current_run_script_file);

    connect(ui->browseRunScriptFileButton, SIGNAL(clicked()), this, SLOT(browseFileAsRunScript()));
}

CConfigureProjectDialog::~CConfigureProjectDialog() {
    delete ui;
}

/*
 * Private slots
 */

void CConfigureProjectDialog::accept() {
    this->_new_run_script_file = ui->newRunScriptFileLabel->text();
    this->close();
    this->setResult(QDialog::Accepted);
}

void CConfigureProjectDialog::browseFileAsRunScript() {
    QFileDialog *file_dialog = new QFileDialog(this);
    ui->newRunScriptFileLabel->setText(file_dialog->getOpenFileName());
}

/*
 * Private functions
 */

QString CConfigureProjectDialog::getNewRunScriptFile() const {
    return _new_run_script_file;
}
