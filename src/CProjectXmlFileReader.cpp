#include "CProjectXmlFileReader.hpp"

#include <iostream>

CProjectXmlFileReader::CProjectXmlFileReader() { }

bool CProjectXmlFileReader::read(QIODevice *device) {
    xml_reader.setDevice(device);

    readXML();

    return !xml_reader.error();
}

void CProjectXmlFileReader::readXML() {
    while (xml_reader.readNextStartElement()) {
        if (xml_reader.name() == "project")
            readProjectTag();
        else if (xml_reader.name() == "name")
            readNameTag();
        else if (xml_reader.name() == "type")
            readTypeTag();
        else if (xml_reader.name() == "location")
            readLocationTag();
        else if (xml_reader.name() == "run_script")
            readRunScriptTag();
        else
            xml_reader.skipCurrentElement();
    }
}

void CProjectXmlFileReader::readProjectTag() {
    std::cout << "Processing <project>...\n";
}

void CProjectXmlFileReader::readNameTag() {
    std::cout << "   Name: " << xml_reader.readElementText().toStdString() << "\n";
}

void CProjectXmlFileReader::readTypeTag() {
    std::cout << "   Type: " << xml_reader.readElementText().toStdString() << "\n";
}

void CProjectXmlFileReader::readLocationTag() {
    std::cout << "   Location: " << xml_reader.readElementText().toStdString() << "\n";
}

void CProjectXmlFileReader::readRunScriptTag() {
    std::cout << "   Run script: " << xml_reader.readElementText().toStdString() << "\n";
}

QString CProjectXmlFileReader::errorString() const {
    return QObject::tr("%1\nLine %2, column %3")
                .arg(xml_reader.errorString())
                .arg(xml_reader.lineNumber())
                .arg(xml_reader.columnNumber());
}
