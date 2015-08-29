#ifndef CPROJECTXMLFILEWRITER_HPP
#define CPROJECTXMLFILEWRITER_HPP

#include "src/model/CProjectModel.hpp"

class CProjectXmlFileWriter {
    public:
        CProjectXmlFileWriter(SProjectInfo const&info);
        bool save();
    private:
        SProjectInfo const& _info;
};

#endif // CPROJECTXMLFILEWRITER_HPP
