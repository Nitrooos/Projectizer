#include "CProjectXmlFileReader.hpp"

#include <QDomDocument>
#include <QFile>

CProjectXmlFileReader::CProjectXmlFileReader(QString file_name) : AXmlFileReader(file_name) { }

SProjectInfo CProjectXmlFileReader::getParsedInformations() const {
    return _project_info;
}

void CProjectXmlFileReader::parseNode(const QDomNode &node) {
    if (node.isElement()) {
        QDomElement element = node.toElement();
        if (element.nodeName() == "name") {
            _project_info._name = element.text();
        } else if (element.nodeName() == "type") {
            _project_info._type = element.text();
        } else if (element.nodeName() == "location") {
            _project_info._location = element.text();
        } else if (element.nodeName() == "run_script") {
            _project_info._run_script = element.text();
        }
    }
}
