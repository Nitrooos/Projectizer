#ifndef CONFIGUREPROJECTDIALOG_HPP
#define CONFIGUREPROJECTDIALOG_HPP

#include <QString>
#include <QDialog>

namespace Ui {
    class ConfigureProjectDialog;
}

struct SProjectInfo;

class CConfigureProjectDialog : public QDialog {
    Q_OBJECT
    public:
        explicit CConfigureProjectDialog(QWidget *parent, SProjectInfo &project_info);
        ~CConfigureProjectDialog();
    private slots:
        void accept();
        void browseFileAsRunScript();
    private:
        Ui::ConfigureProjectDialog *ui;
        SProjectInfo &_edited_project_info;
};

#endif // CONFIGUREPROJECTDIALOG_HPP
