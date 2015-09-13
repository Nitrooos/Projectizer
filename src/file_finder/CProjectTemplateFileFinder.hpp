#ifndef CPROJECTTEMPLATEFILEFINDER_HPP
#define CPROJECTTEMPLATEFILEFINDER_HPP

#include <QDir>

class CProjectTypeItem;

class CProjectTemplateFileFinder {
    public:
        CProjectTemplateFileFinder(QString directory);
        CProjectTypeItem *findTemplateFilesBFS(CProjectTypeItem *rootItem);
    private:
        QString _root_directory;
};

#endif // CPROJECTTEMPLATEFILEFINDER_HPP
