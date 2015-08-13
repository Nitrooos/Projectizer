#include "CXMLFileFinder.hpp"

#include <QDir>

QStringList CXMLFileFinder::getSavedProjectsXMLFiles(QString dir_path) {
    QStringList file_names;
    QFileInfoList file_info_list;
    QDir dir(dir_path);

    if (dir.exists()) {
        QStringList name_filter("*.xml");
        file_info_list = dir.entryInfoList(name_filter);

        foreach (QFileInfo file_info, file_info_list) {
            file_names.push_back(file_info.absoluteFilePath());
        }
    }

    return file_names;
}
