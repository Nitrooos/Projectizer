#include "CXMLFileFinder.hpp"

#include <QDir>

QStringList CXMLFileFinder::getSavedProjectsXMLFiles(QString dir_path) {
    QStringList filenames;
    QDir dir(dir_path);

    if (dir.exists()) {
        QStringList name_filter("*.xml");
        filenames = dir.entryList(name_filter);
    }

    return filenames;
}
