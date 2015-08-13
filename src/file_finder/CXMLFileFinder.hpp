#ifndef CXMLFILEFINDER_HPP
#define CXMLFILEFINDER_HPP

#include <QString>

class CXMLFileFinder {
    public:
        static QStringList getSavedProjectsXMLFiles(QString dir_path);
};

#endif // CXMLFILEFINDER_HPP
