#ifndef CPROJECTXMLFILEREADER_HPP
#define CPROJECTXMLFILEREADER_HPP

#include "AXmlFileReader.hpp"
#include <QMap>

class CProjectXmlFileReader : public AXmlFileReader {
    public:
        CProjectXmlFileReader();

        bool read(QIODevice *device);
    private:
        void readXML();
        void readProjectTag();
        void readNameTag();
        void readTypeTag();
        void readLocationTag();
        void readRunScriptTag();

        QString errorString() const;
        QMap<QString, QString> projectReadData;
};

#endif // CPROJECTXMLFILEREADER_HPP
