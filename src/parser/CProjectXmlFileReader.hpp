#ifndef CPROJECTXMLFILEREADER_HPP
#define CPROJECTXMLFILEREADER_HPP

#include <QXmlStreamReader>
#include <QMap>

class CProjectXmlFileReader {
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

        QXmlStreamReader xml_reader;
        QMap<QString, QString> projectReadData;
};

#endif // CPROJECTXMLFILEREADER_HPP
