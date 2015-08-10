#ifndef CPROJECTXMLFILEREADER_HPP
#define CPROJECTXMLFILEREADER_HPP

#include "AXmlFileReader.hpp"
#include <QString>

class QDomNode;

using namespace std;

struct SProjectInfo {
    QString _name, _type, _location, _run_script;
};

class CProjectXmlFileReader : public AXmlFileReader {
    public:
        CProjectXmlFileReader(QString file_name);
        SProjectInfo getParsedInformations() const;
    protected:
        void parseNode(const QDomNode &node);
    private:
        SProjectInfo _project_info;
};

#endif // CPROJECTXMLFILEREADER_HPP
