#include "AXmlFileReader.hpp"

#include <QDomDocument>
#include <QFile>

bool AXmlFileReader::parse() {
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
