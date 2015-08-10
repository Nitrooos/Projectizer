#ifndef AXMLFILEREADER_HPP
#define AXMLFILEREADER_HPP

#include <QString>
#include <QDomNode>

class AXmlFileReader {
    public:
        AXmlFileReader(QString file_name)
            : _file_name(file_name) {}

        virtual bool parse();
    protected:
        virtual void parseNode(const QDomNode &node) = 0;

        QString _file_name;
};

#endif // AXMLFILEREADER_HPP
