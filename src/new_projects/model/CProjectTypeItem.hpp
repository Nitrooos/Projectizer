#ifndef CPROJECTTYPEITEM_HPP
#define CPROJECTTYPEITEM_HPP

#include <QList>

#include "src/parser/CProjectTypeXmlFileReader.hpp"

struct SProjectTypeItem {
    SProjectTypeItem(const SProjectTypeInfo &info)
        : _info(info), _parent(nullptr) { }

    ~SProjectTypeItem() {
        qDeleteAll(_children);
    }

    SProjectTypeInfo _info;
    SProjectTypeItem *_parent;
    QList<SProjectTypeItem*> _children;
};

#endif // CPROJECTTYPEITEM_HPP
