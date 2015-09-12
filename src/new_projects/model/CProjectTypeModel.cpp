#include "CProjectTypeModel.hpp"
#include "src/new_projects/model/CProjectTypeItem.hpp"

CProjectTypeModel::CProjectTypeModel(QObject *parent) : QAbstractItemModel(parent), _root_node(nullptr) { }

CProjectTypeModel::~CProjectTypeModel() {
    delete this->_root_node;
}

void CProjectTypeModel::setRootNode(SProjectTypeItem *node) {
    delete this->_root_node;
    this->_root_node = node;
}

QModelIndex CProjectTypeModel::index(int row, int column, const QModelIndex &parent) const {
    if (!_root_node || row < 0 || column < 0) {
        return QModelIndex();
    }

    SProjectTypeItem *parentNode = nodeFromIndex(parent);
    SProjectTypeItem *childNode = parentNode->_children.value(row);
    if (!childNode) {
        return QModelIndex();
    }
    return createIndex(row, column, childNode);
}

SProjectTypeItem* CProjectTypeModel::nodeFromIndex(const QModelIndex &index) const {
    if (index.isValid()) {
        return static_cast<SProjectTypeItem*>(index.internalPointer());
    } else {
        return this->_root_node;
    }
}

int CProjectTypeModel::rowCount(const QModelIndex &parent) const {
    if (parent.column() > 0) {
        return 0;
    }
    SProjectTypeItem *parentNode = nodeFromIndex(parent);
    if (!parentNode) {
        return 0;
    }

    return parentNode->_children.count();
}

int CProjectTypeModel::columnCount(const QModelIndex &) const {
    return 2;
}

QModelIndex CProjectTypeModel::parent(const QModelIndex &child) const {
    SProjectTypeItem *node = nodeFromIndex(child);
    if (!node) {
        return QModelIndex();
    }

    SProjectTypeItem *parentNode = node->_parent;
    if (!parentNode) {
        return QModelIndex();
    }

    SProjectTypeItem *grandparentNode = parentNode->_parent;
    if (!grandparentNode) {
        return QModelIndex();
    }

    int row = grandparentNode->_children.indexOf(parentNode);
    return createIndex(row, 0, parentNode);
}

QVariant CProjectTypeModel::data(const QModelIndex &index, int role) const {
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    SProjectTypeItem *node = nodeFromIndex(index);
    if (!node) {
        return QVariant();
    }

    if (index.column() == 0) {
        return node->_info._name;
    }

    return QVariant();
}
