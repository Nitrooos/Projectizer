#ifndef CAPPLICATION_HPP
#define CAPPLICATION_HPP

#include "../windows/main_window/CMainWindow.hpp"

#include <QApplication>
#include <QScopedPointer>

class CMainWindow;

class CApplication : public QApplication {
    public:
        CApplication(int &argc, char *argv[]);
    private:
        void parseArguments();

        QScopedPointer<CMainWindow> _main_window;
        QStringList _parsedPositionalArguments;
};

#endif // CAPPLICATION_HPP
