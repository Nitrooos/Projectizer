#include "CProjectModel.hpp"

CProjectModel::CProjectModel(QObject *parent) : QAbstractTableModel(parent) { }

CProjectModel::CProjectModel(const ProjectInfo &info, QObject *parent) : QAbstractTableModel(parent), info(info) { }

int CProjectModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return info.size();
}

int CProjectModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 2;
}

QVariant CProjectModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() >= info.size() || index.row() < 0) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        ProjectRowInfo pair = info.at(index.row());

        if (index.column() == 0) {
            return pair.first;
        } else if (index.column() == 1) {
            return pair.second.join(", ");
        }
    }

    return QVariant();
}

QVariant CProjectModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:  return tr("Name");
            case 1:  return tr("Technologies");
            default: return QVariant();
        }
    }

    return QVariant();
}

bool CProjectModel::insertRows(int position, int rows, const QModelIndex &index) {
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        QPair<QString, QStringList> pair(" ", QStringList());
        info.insert(position, pair);
    }

    endInsertRows();
    return true;
}

bool CProjectModel::removeRows(int position, int rows, const QModelIndex &index) {
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        info.removeAt(position);
    }

    endRemoveRows();
    return true;
}

bool CProjectModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        QPair<QString, QStringList> p = info.value(row);

        if (index.column() == 0) {
            p.first = value.toString();
        } else if (index.column() == 1) {
            p.second = value.toStringList();
        } else {
            return false;
        }

        info.replace(row, p);
        emit(dataChanged(index, index));

        return true;
    }

    return false;
}

Qt::ItemFlags CProjectModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) {
        return Qt::ItemIsEnabled;
    }

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

ProjectInfo CProjectModel::getList() {
    return info;
}
