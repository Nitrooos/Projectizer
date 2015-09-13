#include "CProjectTypeItem.hpp"

CProjectTypeItem::CProjectTypeItem(const SProjectTypeInfo &info, CProjectTypeItem *parent)
    : _info(info), _parent(parent) { }

CProjectTypeItem::~CProjectTypeItem()  {
    qDeleteAll(this->_children);
}

const SProjectTypeInfo& CProjectTypeItem::getProjectTypeInfo() const {
    return this->_info;
}

void CProjectTypeItem::appendChild(CProjectTypeItem *child) {
    this->_children.append(child);
}

CProjectTypeItem* CProjectTypeItem::child(int row) {
    return this->_children.value(row);
}

int CProjectTypeItem::childCount() const {
    return this->_children.count();
}

int CProjectTypeItem::row() const {
    if (this->_parent) {
        return this->_parent->_children.indexOf(const_cast<CProjectTypeItem*>(this));
    }
    return 0;
}

int CProjectTypeItem::columnCount() const {
    return 1;
}

QVariant CProjectTypeItem::data(int column) const {
    Q_UNUSED(column);
    return this->_info._name;
}

CProjectTypeItem* CProjectTypeItem::parentItem() {
    return this->_parent;
}
