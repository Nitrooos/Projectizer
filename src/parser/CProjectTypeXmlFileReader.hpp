#ifndef CPROJECTTYPEXMLFILEREADER_HPP
#define CPROJECTTYPEXMLFILEREADER_HPP

#include "AXmlFileReader.hpp"

#include <QList>
#include <QString>

class CProjectTypeXmlFileReader : public AXmlFileReader {
    public:
        CProjectTypeXmlFileReader();

        bool read(QIODevice *device);
    private:
        void readProjectTypeTag();
        void readTechnologiesTag();
        void readOptionsTag();

        void printProjectTypeInfo();

        struct SXmlNode {
            QString tag_name, tag_content;
            QXmlStreamAttributes attributes;
            QList<SXmlNode> children;
        };

        QList<SXmlNode> projectTypeData;
};

#endif // CPROJECTTYPEXMLFILEREADER_HPP
