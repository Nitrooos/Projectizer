#ifndef CSAVEDPROJECTSTABLEVIEW_HPP
#define CSAVEDPROJECTSTABLEVIEW_HPP

#include <QTableView>

class CSavedProjectsTableView : public QTableView {
    Q_OBJECT
    public:
        CSavedProjectsTableView(QWidget *parent);
    public slots:
        void onDoubleClick(QModelIndex index);
    private:
        void setup();
        void fillWithSavedProjectsData();
};

#endif // CSAVEDPROJECTSTABLEVIEW_HPP
