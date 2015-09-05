#ifndef CNEWPROJECTDIALOG_HPP
#define CNEWPROJECTDIALOG_HPP

#include <QMainWindow>

namespace Ui {
    class NewProjectWindow;
}

class CNewProjectWindow : public QMainWindow {
    Q_OBJECT
    public:
       CNewProjectWindow(QString const& directory = "", QWidget *parent = 0);
    private:
        Ui::NewProjectWindow *ui;

        QString _directory;
};

#endif // CNEWPROJECTDIALOG_HPP
