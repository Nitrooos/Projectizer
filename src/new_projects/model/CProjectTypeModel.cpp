#include "CProjectTypeModel.hpp"
#include "src/new_projects/model/CProjectTypeItem.hpp"

CProjectTypeModel::CProjectTypeModel(QObject *parent) : QAbstractItemModel(parent) {
    this->_root_item = new CProjectTypeItem(SProjectTypeInfo{"root", {}, {nullptr}});
}

CProjectTypeModel::~CProjectTypeModel() {
    delete this->_root_item;
}

CProjectTypeItem* CProjectTypeModel::getRootItem() {
    return this->_root_item;
}

QModelIndex CProjectTypeModel::index(int row, int column, const QModelIndex &parent) const {
    if (!this->hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    CProjectTypeItem *parentItem;

    if (!parent.isValid()) {
        parentItem = this->_root_item;
    } else {
        parentItem = static_cast<CProjectTypeItem*>(parent.internalPointer());
    }

    CProjectTypeItem *childItem = parentItem->child(row);
    if (childItem) {
        return createIndex(row, column, childItem);
    } else {
        return QModelIndex();
    }
}

QModelIndex CProjectTypeModel::parent(const QModelIndex &index) const {
    if (!index.isValid()) {
        return QModelIndex();
    }

    CProjectTypeItem *childItem = static_cast<CProjectTypeItem*>(index.internalPointer());
    CProjectTypeItem *parentItem = childItem->parentItem();

    if (parentItem == this->_root_item) {
        return QModelIndex();
    }

    return createIndex(parentItem->row(), 0, parentItem);
}

int CProjectTypeModel::rowCount(const QModelIndex &parent) const {
    CProjectTypeItem *parentItem;
    if (parent.column() > 0) {
        return 0;
    }

    if (!parent.isValid()) {
        parentItem = this->_root_item;
    } else {
        parentItem = static_cast<CProjectTypeItem*>(parent.internalPointer());
    }

    return parentItem->childCount();
}

int CProjectTypeModel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return static_cast<CProjectTypeItem*>(parent.internalPointer())->columnCount();
    } else {
        return this->_root_item->columnCount();
    }
}

QVariant CProjectTypeModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    CProjectTypeItem *item = static_cast<CProjectTypeItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags CProjectTypeModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) {
        return 0;
    }

    return QAbstractItemModel::flags(index);
}
