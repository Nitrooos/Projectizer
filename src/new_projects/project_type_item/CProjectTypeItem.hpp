#ifndef CPROJECTTYPEITEM_HPP
#define CPROJECTTYPEITEM_HPP

#include "src/parser/CProjectTypeXmlFileReader.hpp"

#include <QStandardItem>

class CProjectTypeItem : public QStandardItem {
    public:
        CProjectTypeItem(SProjectTypeInfo &info);

        QVariant data(int role) const;
    private:
        SProjectTypeInfo _project_type_info;
};

#endif // CPROJECTTYPEITEM_HPP
