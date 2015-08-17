#include "CConfigureProjectDialog.hpp"
#include "ui_ConfigureProjectDialog.h"

ConfigureProjectDialog::ConfigureProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigureProjectDialog)
{
    ui->setupUi(this);
}

ConfigureProjectDialog::~ConfigureProjectDialog()
{
    delete ui;
}
