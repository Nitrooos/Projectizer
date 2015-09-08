#ifndef CPROJECTTEMPLATEFILEFINDER_HPP
#define CPROJECTTEMPLATEFILEFINDER_HPP

class QDir;
class QStandardItem;

class CProjectTemplateFileFinder {
    public:
        CProjectTemplateFileFinder();
        void findTemplateFilesBFS(QDir directory, QStandardItem *root_item);
};

#endif // CPROJECTTEMPLATEFILEFINDER_HPP
