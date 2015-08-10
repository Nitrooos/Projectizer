#include "CMainWindow.hpp"

#include <QApplication>
#include <QElapsedTimer>

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
    CMainWindow window;
    window.show();

    return app.exec();
}
