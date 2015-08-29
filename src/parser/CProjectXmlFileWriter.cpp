#include "CProjectXmlFileWriter.hpp"

#include <QFile>
#include <QTextStream>

CProjectXmlFileWriter::CProjectXmlFileWriter(const SProjectInfo &info)
    : _info(info) { }

bool CProjectXmlFileWriter::save() {
    QFile file(_info._project_xml_file);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    QDomDocument document;
    QDomElement project = document.createElement("project");

    project.appendChild(this->createElement(document, "name", _info._name));
    project.appendChild(this->createElement(document, "type", _info._type));
    project.appendChild(this->createElement(document, "location", _info._location));
    project.appendChild(this->createElement(document, "run_script", _info._run_script));

    document.appendChild(project);

    QTextStream out(&file);
    out << document.toString(4);

    return true;
}

QDomElement CProjectXmlFileWriter::createElement(QDomDocument document, QString tag_name, QString tag_value) const {
    QDomElement element = document.createElement(tag_name);
    QDomText element_text = document.createTextNode(tag_value);
    element.appendChild(element_text);
    return element;
}
