#include "CProjectTemplateFileFinder.hpp"
#include "src/parser/CProjectTypeXmlFileReader.hpp"
#include "src/new_projects/model/CProjectTypeItem.hpp"

#include <QList>

CProjectTemplateFileFinder::CProjectTemplateFileFinder(QString directory)
    : _root_directory(directory) { }

CProjectTypeItem *CProjectTemplateFileFinder::findTemplateFilesBFS(CProjectTypeItem *rootItem) {
    if (QDir(this->_root_directory).exists()) {
        EntryList entries;
        entries.push_back(qMakePair(QFileInfo(this->_root_directory), rootItem));

        while (!entries.empty()) {
            QDir directory(entries.front().first.absoluteFilePath(), "", QDir::Name);
            CProjectTypeItem *current_parent = entries.front().second;
            entries.pop_front();
            this->findTemplatesInDirectory(directory, current_parent, entries);
        }
    }
    return rootItem;
}

void CProjectTemplateFileFinder::findTemplatesInDirectory(QDir directory, CProjectTypeItem *current_parent, EntryList &entries) {
    for (QFileInfo entry : directory.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs)) {
        SProjectTypeInfo info;
        QDir d(entry.absoluteFilePath(), "", QDir::Name);
        for (QFileInfo file : d.entryInfoList(QStringList() << "*.xml", QDir::NoDotAndDotDot | QDir::Files)) {
            CProjectTypeXmlFileReader reader(file.absoluteFilePath());
            if (reader.parse()) {
                info = reader.getProjectTypeInfo();
                break;
            }
        }

        info._name = entry.baseName();
        info._create_script_path = entry.absoluteFilePath() + "/create.sh";
        auto next_parent = new CProjectTypeItem(info, current_parent);
        current_parent->appendChild(next_parent);
        entries.push_back(qMakePair(entry, next_parent));
    }
}
