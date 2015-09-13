#ifndef CPROJECTTYPEMODEL_HPP
#define CPROJECTTYPEMODEL_HPP

#include <QModelIndex>

class CProjectTypeItem;

class CProjectTypeModel : public QAbstractItemModel {
    Q_OBJECT
    public:
        explicit CProjectTypeModel(QObject *parent = 0);
        ~CProjectTypeModel();

        CProjectTypeItem* getRootItem();

        QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
        Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
        QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
        int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
        int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    private:
        CProjectTypeItem *_root_item;
};

#endif // CPROJECTTYPEMODEL_HPP
