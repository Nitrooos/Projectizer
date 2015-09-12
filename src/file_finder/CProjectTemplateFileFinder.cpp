#include "CProjectTemplateFileFinder.hpp"
#include "src/new_projects/model/CProjectTypeItem.hpp"

#include <QList>

CProjectTemplateFileFinder::CProjectTemplateFileFinder(QString directory)
    : _root_directory(directory), _root_item(nullptr) { }

#include <iostream>
SProjectTypeItem* CProjectTemplateFileFinder::findTemplateFilesBFS() {
    this->_root_item = new SProjectTypeItem(SProjectTypeInfo{});

    if (QDir(this->_root_directory).exists()) {
        QList<QPair<QFileInfo, SProjectTypeItem*>> entries;
        entries.push_back(qMakePair(this->_root_directory, this->_root_item));

        while (!entries.empty()) {
            QDir directory(entries.front().first.absoluteFilePath(), "", QDir::Name);
            SProjectTypeItem *current_parent = entries.front().second;
            entries.pop_front();
            
            for (QFileInfo entry : directory.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs)) {
                SProjectTypeInfo info{entry.baseName(), {"test1", "test2", "test3"}, {nullptr}};
                auto new_parent = new SProjectTypeItem(info);

                current_parent->_children.push_back(new_parent);
                entries.push_back(qMakePair(entry, new_parent));
                std::cout << entries.back().first.absoluteFilePath().toStdString() << "\n";
            }

            for (QFileInfo file : directory.entryInfoList(QStringList() << "*.xml", QDir::NoDotAndDotDot | QDir::Files)) {
                std::cout << file.absoluteFilePath().toStdString() << "\n";
            }
        }
    }

    return this->_root_item;
}
