#ifndef CPROJECTXMLFILEREADER_HPP
#define CPROJECTXMLFILEREADER_HPP

#include <QXmlStreamReader>

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
};

#endif // CPROJECTXMLFILEREADER_HPP
