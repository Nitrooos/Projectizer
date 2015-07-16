#ifndef AXMLFILEREADER_HPP
#define AXMLFILEREADER_HPP

#include <QXmlStreamReader>

class AXmlFileReader : public QXmlStreamReader {
    public:
        virtual bool read(QIODevice *device) = 0;
    protected:
        QXmlStreamReader xml_reader;
};

#endif // AXMLFILEREADER_HPP
