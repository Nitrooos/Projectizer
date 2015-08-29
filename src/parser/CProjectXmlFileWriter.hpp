#ifndef CPROJECTXMLFILEWRITER_HPP
#define CPROJECTXMLFILEWRITER_HPP

#include "src/model/CProjectModel.hpp"

#include <QDomElement>

class CProjectXmlFileWriter {
    public:
        CProjectXmlFileWriter(SProjectInfo const&info);
        bool save();
    private:
        QDomElement createElement(QDomDocument document, QString tag_name, QString tag_value) const;

        SProjectInfo const& _info;
};

#endif // CPROJECTXMLFILEWRITER_HPP
