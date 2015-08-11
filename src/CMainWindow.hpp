#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class CMainWindow;
}

class CMainWindow : public QMainWindow {
    Q_OBJECT
    public:
        explicit CMainWindow(QWidget *parent = 0);
        ~CMainWindow();

    private:
        void centerWindow();
        void hideRemoveAndConfigureButtons() const;

        Ui::CMainWindow *ui;
};

#endif // CMAINWINDOW_H
