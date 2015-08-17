#ifndef CONFIGUREPROJECTDIALOG_HPP
#define CONFIGUREPROJECTDIALOG_HPP

#include <QDialog>

namespace Ui {
    class ConfigureProjectDialog;
}

class ConfigureProjectDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit ConfigureProjectDialog(QWidget *parent = 0);
        ~ConfigureProjectDialog();

    private:
        Ui::ConfigureProjectDialog *ui;
};

#endif // CONFIGUREPROJECTDIALOG_HPP
