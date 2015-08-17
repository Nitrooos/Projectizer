#ifndef CONFIGUREPROJECTDIALOG_HPP
#define CONFIGUREPROJECTDIALOG_HPP

#include <QString>
#include <QDialog>

namespace Ui {
    class ConfigureProjectDialog;
}

class CConfigureProjectDialog : public QDialog {
    Q_OBJECT
    public:
        explicit CConfigureProjectDialog(QWidget *parent = 0);
        ~CConfigureProjectDialog();

        QString getNewRunScriptFile() const;
    private slots:
        void accept();
    private:
        Ui::ConfigureProjectDialog *ui;
        QString _new_run_script_file;
};

#endif // CONFIGUREPROJECTDIALOG_HPP
