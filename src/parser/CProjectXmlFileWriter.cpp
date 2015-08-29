#include "CProjectXmlFileWriter.hpp"

#include <QFile>
#include <QTextStream>

CProjectXmlFileWriter::CProjectXmlFileWriter(const SProjectInfo &info)
    : _info(info) { }

bool CProjectXmlFileWriter::save() {
    QDomDocument document;
    QFile file(_info._project_xml_file);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    QDomElement project = document.createElement("project");

    QDomElement name = document.createElement("name");
    QDomText name_text = document.createTextNode(_info._name);
    name.appendChild(name_text);
    project.appendChild(name);

    QDomElement type = document.createElement("type");
    QDomText type_text = document.createTextNode(_info._type);
    type.appendChild(type_text);
    project.appendChild(type);

    QDomElement location = document.createElement("location");
    QDomText location_text = document.createTextNode(_info._location);
    location.appendChild(location_text);
    project.appendChild(location);

    QDomElement run_script = document.createElement("run_script");
    QDomText run_script_text = document.createTextNode(_info._run_script);
    run_script.appendChild(run_script_text);
    project.appendChild(run_script);

    document.appendChild(project);

    QTextStream out(&file);
    out << document.toString(4);

    return true;
}
