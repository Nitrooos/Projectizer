#include "CConfigureProjectDialog.hpp"
#include "ui_ConfigureProjectDialog.h"

CConfigureProjectDialog::CConfigureProjectDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::ConfigureProjectDialog)
{
    ui->setupUi(this);
}

CConfigureProjectDialog::~CConfigureProjectDialog() {
    delete ui;
}

/*
 * Private slots
 */

void CConfigureProjectDialog::accept() {
    this->_new_run_script_file = ui->newRunScriptFileLabel->text();
}

/*
 * Private functions
 */

QString CConfigureProjectDialog::getNewRunScriptFile() const {
    return _new_run_script_file;
}
