#ifndef CPROJECTTEMPLATEFILEFINDER_HPP
#define CPROJECTTEMPLATEFILEFINDER_HPP

#include <QDir>

class QStandardItem;

class CProjectTemplateFileFinder {
    public:
        CProjectTemplateFileFinder(QString directory, QStandardItem *root_item);
        QStandardItem *findTemplateFilesBFS();
    private:
        QString _root_directory;
        QStandardItem *_root_item;
};

#endif // CPROJECTTEMPLATEFILEFINDER_HPP
