#include "CProjectXmlFileReader.hpp"

#include <iostream>
#include <QSet>

CProjectXmlFileReader::CProjectXmlFileReader() { }

bool CProjectXmlFileReader::read(QIODevice *device) {
    xml_reader.setDevice(device);
    readXML();
    return !xml_reader.error();
}

void CProjectXmlFileReader::readXML() {
    bool project_tag_read = false;
    while (!project_tag_read && xml_reader.readNextStartElement()) {
        if (xml_reader.name() == "project") {
            readProjectTag();
            project_tag_read = true;
        } else {
            xml_reader.skipCurrentElement();
        }
    }
}

void CProjectXmlFileReader::readProjectTag() {
    const QSet<QString> VALID_TAGS_INSIDE_PROJECT = {"name", "type", "location", "run_script"};

    while (xml_reader.readNextStartElement()) {
        if (VALID_TAGS_INSIDE_PROJECT.find(xml_reader.name().toString()) != VALID_TAGS_INSIDE_PROJECT.end()) {
            projectReadData[xml_reader.name().toString()] = xml_reader.readElementText();
        } else {
            xml_reader.skipCurrentElement();
        }
    }
}

QString CProjectXmlFileReader::errorString() const {
    return QObject::tr("%1\nLine %2, column %3")
                .arg(xml_reader.errorString())
                .arg(xml_reader.lineNumber())
                .arg(xml_reader.columnNumber());
}
