#include "CMainWindow.hpp"
#include "parser/CProjectXmlFileReader.hpp"

#include <QApplication>
#include <QFile>
#include <QMessageBox>

#include <iostream>

int main(int argc, char *argv[])
{
    /*QApplication app(argc, argv);
    CMainWindow w;
    w.show();

    return app.exec();*/

    CProjectXmlFileReader *reader = new CProjectXmlFileReader();

    QString file_name = "../Projectizer/project.xml";
    QFile file(file_name);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        std::cerr << "Cannot open read file: " << file_name.toStdString() << ": " << file.errorString().toStdString() << "\n";
        return -1;
    }
    reader->read(&file);

    return 0;
}
