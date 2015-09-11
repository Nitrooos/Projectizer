#ifndef CPROJECTTYPEITEM_HPP
#define CPROJECTTYPEITEM_HPP

#include <QList>

struct SProjectTypeInfo;

struct SProjectTypeItem {
    SProjectTypeItem(SProjectTypeInfo *info)
        : _info(info), _parent(nullptr) { }

    ~SProjectTypeItem() {
        qDeleteAll(_children);
    }

    SProjectTypeItem *_parent;
    QList<SProjectTypeItem*> _children;

    SProjectTypeInfo *_info;
};

#endif // CPROJECTTYPEITEM_HPP
