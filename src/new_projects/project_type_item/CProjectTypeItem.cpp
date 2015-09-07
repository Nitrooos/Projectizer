#include "src/new_projects/project_type_item/CProjectTypeItem.hpp"

CProjectTypeItem::CProjectTypeItem(SProjectTypeInfo &info) : _project_type_info(info) { }

QVariant CProjectTypeItem::data(int role) const {
    if (role == Qt::DisplayRole) {
        return _project_type_info._name;
    }

    return QVariant();
}
