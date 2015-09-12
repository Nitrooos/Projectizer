#ifndef CPROJECTTEMPLATEFILEFINDER_HPP
#define CPROJECTTEMPLATEFILEFINDER_HPP

#include <QDir>

class SProjectTypeItem;

class CProjectTemplateFileFinder {
    public:
        CProjectTemplateFileFinder(QString directory);
        SProjectTypeItem *findTemplateFilesBFS();
    private:
        QString _root_directory;
        SProjectTypeItem *_root_item;
};

#endif // CPROJECTTEMPLATEFILEFINDER_HPP
