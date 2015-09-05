#include "CProjectModel.hpp"

CProjectModel::CProjectModel(QObject *parent) : QAbstractTableModel(parent) { }

CProjectModel::CProjectModel(const QList<SProjectInfo> &info, QObject *parent) : QAbstractTableModel(parent), saved_projects_info(info) { }

int CProjectModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return saved_projects_info.size();
}

int CProjectModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 2;
}

QVariant CProjectModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() >= saved_projects_info.size() || index.row() < 0) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        SProjectInfo project_info = saved_projects_info.at(index.row());

        if (index.column() == 0) {
            return project_info._name;
        } else if (index.column() == 1) {
            return project_info._type;
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
            case 1:  return tr("Technology");
            default: return QVariant();
        }
    }

    return QVariant();
}

bool CProjectModel::insertRows(int position, int rows, const QModelIndex &index) {
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        SProjectInfo project_info;
        saved_projects_info.insert(position, project_info);
    }

    endInsertRows();
    return true;
}

bool CProjectModel::removeRows(int position, int rows, const QModelIndex &index) {
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        saved_projects_info.removeAt(position);
    }

    endRemoveRows();
    return true;
}

bool CProjectModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        SProjectInfo p = saved_projects_info.value(row);

        if (index.column() == 0) {
            p._name = value.toString();
        } else if (index.column() == 1) {
            p._type = value.toString();
        } else {
            return false;
        }

        saved_projects_info.replace(row, p);
        emit(dataChanged(index, index));

        return true;
    }

    return false;
}

Qt::ItemFlags CProjectModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) {
        return Qt::ItemIsEnabled;
    }

    return QAbstractTableModel::flags(index);
}

QList<SProjectInfo> CProjectModel::getList() {
    return saved_projects_info;
}

SProjectInfo &CProjectModel::getItem(int index) {
    return saved_projects_info[index];
}
