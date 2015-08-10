#ifndef CPROJECTMODEL_HPP
#define CPROJECTMODEL_HPP

#include <QAbstractTableModel>

typedef QPair<QString, QStringList> ProjectRowInfo;
typedef QList<ProjectRowInfo> ProjectInfo;

class CProjectModel : public QAbstractTableModel {
    public:
        CProjectModel(QObject *parent = 0);
        CProjectModel(ProjectInfo const& info, QObject *parent = 0);

        int rowCount(const QModelIndex &parent) const;
        int columnCount(const QModelIndex &parent) const;
        QVariant data(const QModelIndex &index, int role) const;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const;
        Qt::ItemFlags flags(const QModelIndex &index) const;
        bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
        bool insertRows(int position, int rows, const QModelIndex &index=QModelIndex());
        bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex());
        ProjectInfo getList();
    private:
        ProjectInfo info;
};

#endif // CPROJECTMODEL_HPP
