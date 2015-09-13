#include "CProjectTemplateFileFinder.hpp"
#include "src/new_projects/model/CProjectTypeItem.hpp"

#include <QList>

CProjectTemplateFileFinder::CProjectTemplateFileFinder(QString directory)
    : _root_directory(directory) { }

#include <iostream>
CProjectTypeItem *CProjectTemplateFileFinder::findTemplateFilesBFS(CProjectTypeItem *rootItem) {
    if (QDir(this->_root_directory).exists()) {
        QList<QPair<QFileInfo, CProjectTypeItem*>> entries;
        entries.push_back(qMakePair(QFileInfo(this->_root_directory), rootItem));

        while (!entries.empty()) {
            QDir directory(entries.front().first.absoluteFilePath(), "", QDir::Name);
            CProjectTypeItem *current_parent = entries.front().second;
            entries.pop_front();
            
            for (QFileInfo entry : directory.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs)) {
                SProjectTypeInfo info{entry.baseName(), {"test1", "test2", "test3"}, {nullptr}};
                auto new_parent = new CProjectTypeItem(info, current_parent);

                current_parent->appendChild(new_parent);
                entries.push_back(qMakePair(entry, new_parent));
                std::cout << entry.absoluteFilePath().toStdString() << "\n";
            }

            for (QFileInfo file : directory.entryInfoList(QStringList() << "*.xml", QDir::NoDotAndDotDot | QDir::Files)) {
                std::cout << file.absoluteFilePath().toStdString() << "\n";
            }
        }
    }

    return rootItem;
}
