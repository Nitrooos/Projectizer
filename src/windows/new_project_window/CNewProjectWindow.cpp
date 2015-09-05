#include "CNewProjectWindow.hpp"
#include "ui_NewProjectWindow.h"

CNewProjectWindow::CNewProjectWindow(const QString &directory, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::NewProjectWindow),  _directory(directory)
{
    ui->setupUi(this);
    ui->label->setText(_directory);
}
