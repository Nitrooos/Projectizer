#include "CApplication.hpp"

#include <QCommandLineParser>

CApplication::CApplication(int &argc, char *argv[]) : QApplication(argc, argv) {
    QApplication::setApplicationName("Projectizer");
    QApplication::setApplicationVersion("0.1");

    this->parseArguments();

    this->_main_window.reset(new CMainWindow());
    this->_main_window->show();
}

void CApplication::parseArguments() {
    QCommandLineParser parser;
    parser.setApplicationDescription("Test helper");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("directory", QApplication::translate("main", "Directory to run application in mode 'Create new project'"));
    parser.process(*this);

    this->_parsedPositionalArguments = parser.positionalArguments();
}
