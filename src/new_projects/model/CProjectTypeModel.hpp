#ifndef CPROJECTTYPEMODEL_HPP
#define CPROJECTTYPEMODEL_HPP

#include <QModelIndex>

class SProjectTypeItem;

class CProjectTypeModel : public QAbstractItemModel {
    public:
        CProjectTypeModel(QObject *parent = 0);
        ~CProjectTypeModel();

        void setRootNode(SProjectTypeItem *node);

        QModelIndex index(int row, int column, const QModelIndex &parent) const;
        QModelIndex parent(const QModelIndex &child) const;

        int rowCount(const QModelIndex &parent) const;
        int columnCount(const QModelIndex &parent) const;
        QVariant data(const QModelIndex &index, int role) const;
    private:
        SProjectTypeItem *nodeFromIndex(const QModelIndex &index) const;

        SProjectTypeItem *_root_node;
};

#endif // CPROJECTTYPEMODEL_HPP
