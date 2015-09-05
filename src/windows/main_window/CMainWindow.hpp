#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include "../new_project_window/CNewProjectWindow.hpp"

#include <QMainWindow>

namespace Ui {
    class CMainWindow;
}

class CMainWindow : public QMainWindow {
    Q_OBJECT
    public:
        explicit CMainWindow(QWidget *parent = 0);
        ~CMainWindow();
    public slots:
        void handleTableViewSelectionChange();
        void runConfigureProjectDialog();
        void runNewProjectWindow();
    private:
        void keyPressEvent(QKeyEvent *event);
        void centerWindow();
        void setRemoveAndConfigureButtonsVisibility(bool visible) const;

        Ui::CMainWindow *ui;
        QScopedPointer<CNewProjectWindow> _new_project_window;
};

#endif // CMAINWINDOW_H
