#ifndef CPROJECTXMLFILEREADER_HPP
#define CPROJECTXMLFILEREADER_HPP

#include <QString>

class QDomNode;

using namespace std;

struct SProjectInfo {
    QString _name, _type, _location, _run_script;
};

class CProjectXmlFileReader {
    public:
        CProjectXmlFileReader(QString file_name);
        bool parse();
        SProjectInfo getParsedInformations() const;
    private:
        void parseNode(const QDomNode &node);

        QString _file_name;
        SProjectInfo _project_info;
};

#endif // CPROJECTXMLFILEREADER_HPP
