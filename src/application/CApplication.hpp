#ifndef CAPPLICATION_HPP
#define CAPPLICATION_HPP

#include "../windows/main_window/CMainWindow.hpp"
#include "../windows/new_project_window/CNewProjectWindow.hpp"

#include <QApplication>
#include <QScopedPointer>

class CMainWindow;

class CApplication : public QApplication {
    public:
        CApplication(int &argc, char *argv[]);
    private:
        void parseArguments();

        QScopedPointer<CMainWindow> _main_window;
        QScopedPointer<CNewProjectWindow> _new_project_window;
        QScopedPointer<QString> _new_project_directory;
};

#endif // CAPPLICATION_HPP
