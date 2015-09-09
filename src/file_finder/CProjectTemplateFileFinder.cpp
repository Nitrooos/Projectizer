#include "CProjectTemplateFileFinder.hpp"

#include "src/new_projects/project_type_item/CProjectTypeItem.hpp"

#include <QStandardItem>
#include <QList>

CProjectTemplateFileFinder::CProjectTemplateFileFinder(QString directory, QStandardItem *root_item)
    : _root_directory(directory), _root_item(root_item) { }

#include <iostream>
QStandardItem* CProjectTemplateFileFinder::findTemplateFilesBFS() {
    if (QDir(this->_root_directory).exists()) {
        QList<QPair<QFileInfo, QStandardItem*>> entries;
        entries.push_back(qMakePair(this->_root_directory, this->_root_item));

        while (!entries.empty()) {
            QDir directory(entries.front().first.absoluteFilePath(), "", QDir::Name);
            QStandardItem *current_parent = entries.front().second;
            entries.pop_front();
            
            for (QFileInfo entry : directory.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs)) {
                SProjectTypeInfo info{entry.baseName(), {"test1", "test2", "test3"}, {nullptr}};
                QList<QStandardItem*> new_parent;
                new_parent << new CProjectTypeItem(info);

                current_parent->appendRow(new_parent);
                entries.push_back(qMakePair(entry, new_parent.first()));
                std::cout << entries.back().first.absoluteFilePath().toStdString() << "\n";
            }

            for (QFileInfo file : directory.entryInfoList(QStringList() << "*.xml", QDir::NoDotAndDotDot | QDir::Files)) {
                std::cout << file.absoluteFilePath().toStdString() << "\n";
            }
        }
    }

    return _root_item;
}
