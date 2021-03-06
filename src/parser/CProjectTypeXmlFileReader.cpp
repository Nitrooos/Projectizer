#include "CProjectTypeXmlFileReader.hpp"
#include "COption.hpp"

#include <QDomDocument>
#include <QFile>

CProjectTypeXmlFileReader::CProjectTypeXmlFileReader(QString file_name) : AXmlFileReader(file_name) { }

SProjectTypeInfo CProjectTypeXmlFileReader::getProjectTypeInfo() const {
    return _project_type_info;
}

void CProjectTypeXmlFileReader::parseNode(const QDomNode &node) {
    if (node.isElement()) {
        QDomElement element = node.toElement();
        if (element.nodeName() == "name") {
            _project_type_info._name = element.text();
        } else if (element.nodeName() == "technologies") {
            readTechnologies(element.childNodes());
        } else if (element.nodeName() == "options") {
            readOptions(element.childNodes());
        }
    }
}

void CProjectTypeXmlFileReader::readTechnologies(const QDomNodeList &node_list) {
    for (int i = 0; i < node_list.size(); ++i) {
        QDomNode node = node_list.item(i);
        if (node.isElement()) {
            _project_type_info._technologies.push_back(node.toElement().text());
        }
    }
}

void CProjectTypeXmlFileReader::readOptions(const QDomNodeList &node_list) {
    for (int i = 0; i < node_list.size(); ++i) {
        QDomNode type = node_list.item(i).attributes().namedItem("type");
        if (!type.isNull()) {
            COption *option = COption::getOptionPerType(type.toAttr().value());
            if (option != nullptr) {
                option->fill(node_list.item(i));
                _project_type_info._options.push_back(option);
            }
        } else {
            continue;
        }
    }
}
