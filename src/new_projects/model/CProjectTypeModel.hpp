#ifndef CPROJECTTYPEMODEL_HPP
#define CPROJECTTYPEMODEL_HPP

#include <QModelIndex>

class SProjectTypeItem;

class CProjectTypeModel : public QABstractItemModel {
    public:
        CProjectTypeModel(QObject *parent = 0);
        ~CProjectTypeModel();

        void setRootNode(Node *node);

        QModelIndex index(int row, int column, const QModelIndex &parent) const;
        QModelIndex parent(const QModelIndex &child) const;

        int rowCount(const QModelIndex &parent) const;
        int columnCount(const QModelIndex &parent) const;
        QVariant data(const QModelIndex &index, int role) const;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    private:
        SProjectTypeItem *_nodeFromIndex(const QModelIndex &index) const;
        SProjectTypeItem *_rootNode;
};

#endif // CPROJECTTYPEMODEL_HPP
