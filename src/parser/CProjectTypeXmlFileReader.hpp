#ifndef CPROJECTTYPEXMLFILEREADER_HPP
#define CPROJECTTYPEXMLFILEREADER_HPP

#include "AXmlFileReader.hpp"
#include "COption.hpp"

#include <QList>

struct SProjectTypeInfo {
    QString _name, _create_script_dir;
    QList<QString> _technologies;
    QList<COption*> _options;

    QString print() const;
};

class CProjectTypeXmlFileReader : public AXmlFileReader {
    public:
        CProjectTypeXmlFileReader(QString file_name);
        SProjectTypeInfo getProjectTypeInfo() const;
    protected:
        void parseNode(const QDomNode &node);
    private:
        void readTechnologies(const QDomNodeList &node_list);
        void readOptions(const QDomNodeList &node_list);

        SProjectTypeInfo _project_type_info;
};

#endif // CPROJECTTYPEXMLFILEREADER_HPP
