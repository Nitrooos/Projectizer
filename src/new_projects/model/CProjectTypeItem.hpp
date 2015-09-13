#ifndef CPROJECTTYPEITEM_HPP
#define CPROJECTTYPEITEM_HPP

#include <QList>
#include <QVariant>

#include "src/parser/CProjectTypeXmlFileReader.hpp"

class CProjectTypeItem {
    public:
        CProjectTypeItem(const SProjectTypeInfo &info, CProjectTypeItem *parent = nullptr);
        ~CProjectTypeItem();

        void appendChild(CProjectTypeItem *child);
        const SProjectTypeInfo &getProjectTypeInfo() const;

        CProjectTypeItem* child(int row);
        int childCount() const;
        int columnCount() const;
        QVariant data(int column) const;
        int row() const;
        CProjectTypeItem* parentItem();
    private:
        SProjectTypeInfo _info;
        CProjectTypeItem *_parent;
        QList<CProjectTypeItem*> _children;
};

#endif // CPROJECTTYPEITEM_HPP
