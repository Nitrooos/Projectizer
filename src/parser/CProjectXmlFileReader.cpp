#include "CProjectXmlFileReader.hpp"

#include <QDomDocument>
#include <QFile>

CProjectXmlFileReader::CProjectXmlFileReader(QString file_name) : _file_name(file_name) { }

bool CProjectXmlFileReader::parse() {
    QDomDocument document;
    QFile file(_file_name);

    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    if (!document.setContent(&file)) {
        file.close();
        return false;
    }
    file.close();

    QDomElement root = document.documentElement();
    QDomNodeList root_children = root.childNodes();
    for (int i = 0; i < root_children.size(); ++i) {
        parseNode(root_children.item(i));
    }

    return true;
}

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
