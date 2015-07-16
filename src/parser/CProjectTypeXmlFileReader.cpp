#include "CProjectTypeXmlFileReader.hpp"

CProjectTypeXmlFileReader::CProjectTypeXmlFileReader() { }

bool CProjectTypeXmlFileReader::read(QIODevice *device) {
    xml_reader.setDevice(device);

    bool project_type_tag_read = false;
    while (!project_type_tag_read && xml_reader.readNextStartElement()) {
        if (xml_reader.name() == "project_type") {
            readProjectTypeTag();
            project_type_tag_read = true;
        } else {
            xml_reader.skipCurrentElement();
        }
    }
}

void CProjectTypeXmlFileReader::readProjectTypeTag() {
    while (xml_reader.readNextStartElement()) {
        if (xml_reader.name() == "name") {
            projectTypeData.push_back(SXmlNode{xml_reader.name().toString(), xml_reader.readElementText()});
        } else if (xml_reader.name() == "technologies") {
            readTechnologiesTag();
        } else if (xml_reader.name() == "options") {
            readOptionsTag();
        } else {
            xml_reader.skipCurrentElement();
        }
    }
}

void CProjectTypeXmlFileReader::readTechnologiesTag() {
    projectTypeData.push_back(SXmlNode{"technologies"});
    SXmlNode technologies = projectTypeData.back();

    while (xml_reader.readNextStartElement()) {
        if (xml_reader.name() == "technology") {
            technologies.children.push_back(SXmlNode{xml_reader.name().toString(), xml_reader.readElementText()});
        } else {
            xml_reader.skipCurrentElement();
        }
    }
}

void CProjectTypeXmlFileReader::readOptionsTag() {
    while (xml_reader.readNextStartElement()) {

    }
}
