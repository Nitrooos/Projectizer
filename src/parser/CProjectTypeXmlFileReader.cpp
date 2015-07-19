#include "CProjectTypeXmlFileReader.hpp"

#include <iostream>
#include <QSet>

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
        if (xml_reader.name() == "option") {
            readOptionTag();
        } else {
            xml_reader.skipCurrentElement();
        }
    }
}

void CProjectTypeXmlFileReader::readOptionTag() {
    const QSet<QString> VALID_OPTION_TYPES = {"checkbox", "radio", "text", "selectbox"};

    QString option_type = xml_reader.attributes().value("type").toString();
    if (VALID_OPTION_TYPES.find(option_type) != VALID_OPTION_TYPES.end()) {
        while (xml_reader.readNextStartElement()) {
            if (option_type == "checkbox") {
                readOptionCheckboxTag();
            } else if (option_type == "text") {
                readOptionTextTag();
            } else if (option_type == "radio") {
                //readOptionRadioTag();
            } else if (option_type == "selectbox") {
                //readOptionSelectboxTag();
            }
        }
    } else {
        xml_reader.skipCurrentElement();
    }
}

void CProjectTypeXmlFileReader::readOptionCheckboxTag() {
    projectTypeData.push_back(SXmlNode{"checkbox", "", xml_reader.attributes()});
    SXmlNode option_checkbox_tag = projectTypeData.back();

    while (xml_reader.readNextStartElement()) {
        if (xml_reader.name() == "name") {
            option_checkbox_tag.children.push_back(SXmlNode{xml_reader.name().toString(), xml_reader.readElementText()});
        } else if (xml_reader.name() == "label") {
            option_checkbox_tag.children.push_back(SXmlNode{xml_reader.name().toString(), xml_reader.readElementText()});
        } else {
            xml_reader.skipCurrentElement();
        }
    }
}

void CProjectTypeXmlFileReader::readOptionTextTag() {
    projectTypeData.push_back(SXmlNode{"text", "", xml_reader.attributes()});
    SXmlNode option_checkbox_tag = projectTypeData.back();

    while (xml_reader.readNextStartElement()) {
        if (xml_reader.name() == "name") {
            option_checkbox_tag.children.push_back(SXmlNode{xml_reader.name().toString(), xml_reader.readElementText()});
        } else {
            xml_reader.skipCurrentElement();
        }
    }
}

void CProjectTypeXmlFileReader::print() {
    for (auto node : projectTypeData) {
        node.print();
    }
}

void CProjectTypeXmlFileReader::SXmlNode::print() {
    std::cout << "<" << tag_name.toStdString() << ">" << tag_content.toStdString() << "</" << tag_name.toStdString() << ">\n";
    for (auto child : children) {
        child.print();
    }
}
