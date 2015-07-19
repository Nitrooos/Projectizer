#ifndef CPROJECTTYPEXMLFILEREADER_HPP
#define CPROJECTTYPEXMLFILEREADER_HPP

#include "AXmlFileReader.hpp"

#include <QList>
#include <QString>

class CProjectTypeXmlFileReader : public AXmlFileReader {
    public:
        CProjectTypeXmlFileReader();

        bool read(QIODevice *device);
        void print();
    private:
        void readProjectTypeTag();
        void readTechnologiesTag();
        void readOptionsTag();
        void readOptionTag();

        void readOptionCheckboxTag();
        void readOptionTextTag();
        void readOptionRadioTag();
        void readOptionSelectboxTag();

        void printProjectTypeInfo();

        struct SXmlNode {
            QString tag_name, tag_content;
            QXmlStreamAttributes attributes;
            QList<SXmlNode> children;

            void print();
        };

        QList<SXmlNode> projectTypeData;
};

#endif // CPROJECTTYPEXMLFILEREADER_HPP
