#ifndef CPROJECTTEMPLATEFILEFINDER_HPP
#define CPROJECTTEMPLATEFILEFINDER_HPP

#include <QDir>

class CProjectTypeItem;

class CProjectTemplateFileFinder {
    typedef QList<QPair<QFileInfo, CProjectTypeItem*>> EntryList;

    public:
        CProjectTemplateFileFinder(QString directory);
        CProjectTypeItem *findTemplateFilesBFS(CProjectTypeItem *rootItem);
    private:
        void findTemplatesInDirectory(QDir directory, CProjectTypeItem *current_parent, EntryList &entries);

        QString _root_directory;
};

#endif // CPROJECTTEMPLATEFILEFINDER_HPP
