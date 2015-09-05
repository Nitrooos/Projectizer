#include "CApplication.hpp"

#include <QDir>
#include <QCommandLineParser>

CApplication::CApplication(int &argc, char *argv[]) : QApplication(argc, argv) {
    QApplication::setApplicationName("Projectizer");
    QApplication::setApplicationVersion("0.1");

    this->parseArguments();

    if (this->_new_project_directory) {
        // tryb tworzenia nowego projektu
    } else {
        // tryb do przeglądania zapisanych projektów
        this->_main_window.reset(new CMainWindow());
        this->_main_window->show();
    }
}

void CApplication::parseArguments() {
    QCommandLineParser parser;
    parser.setApplicationDescription("Test helper");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("directory", QApplication::translate("main", "Directory to run application in mode 'Create new project'"));
    parser.process(*this);

    if (parser.positionalArguments().length() > 0) {
        QString given_directory = parser.positionalArguments().at(0);
        if (QDir(given_directory).exists()) {
            this->_new_project_directory.reset(new QString(given_directory));
        }
    }
}
