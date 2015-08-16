#ifndef CPROJECTXMLFILEREADER_HPP
#define CPROJECTXMLFILEREADER_HPP

#include "AXmlFileReader.hpp"
#include <QString>

class QDomNode;

using namespace std;

struct SProjectInfo {
    QString _name, _type, _location, _run_script, _project_xml_file;
};

class CProjectXmlFileReader : public AXmlFileReader {
    public:
        CProjectXmlFileReader(QString file_name);
        bool parse();
        SProjectInfo getParsedInformations() const;
    protected:
        void parseNode(const QDomNode &node);
    private:
        SProjectInfo _project_info;
};

#endif // CPROJECTXMLFILEREADER_HPP
