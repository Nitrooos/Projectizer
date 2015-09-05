#include "windows/main_window/CMainWindow.hpp"

#include <QApplication>
#include <QCommandLineParser>
//#include <QElapsedTimer>

#include <iostream>

int main(int argc, char *argv[]) {
    /*CProjectXmlFileReader reader("../Projectizer/project.xml");
    QElapsedTimer timer;
    timer.start();
    if (reader.parse()) {
        SProjectInfo p = reader.getParsedInformations();
        quint64 nsecs = timer.nsecsElapsed();
        std::cout << "Czas parsowania: " << nsecs/1000 << "us\n";
        std::cout << p._name.toStdString() << " " << p._type.toStdString() << " " << p._location.toStdString() << " " << p._run_script.toStdString() << "\n";
    }*/

    /*CProjectTypeXmlFileReader reader("../Projectizer/project_type.xml");
    QElapsedTimer timer;
    timer.start();
    if (reader.parse()) {
        SProjectTypeInfo p = reader.getProjectTypeInfo();
        quint64 nsecs = timer.nsecsElapsed();
        std::cout << "Czas parsowania: " << nsecs/1000 << "us\n";
        std::cout << p.print().toStdString();
    }*/


    QApplication app(argc, argv);
    /*QApplication::setApplicationName("Projectizer");
    QApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("Test helper");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("directory", QApplication::translate("main", "Directory to run application in mode 'Create new project'"));
    parser.process(app);

    const QStringList args = parser.positionalArguments();*/

    CMainWindow window;
    window.show();

    return app.exec();
}
