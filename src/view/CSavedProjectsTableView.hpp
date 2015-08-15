#ifndef CSAVEDPROJECTSTABLEVIEW_HPP
#define CSAVEDPROJECTSTABLEVIEW_HPP

#include "src/model/CProjectModel.hpp"
#include <QProcess>
#include <QTableView>

class CSavedProjectsTableView : public QTableView {
    Q_OBJECT
    public:
        CSavedProjectsTableView(QWidget *parent);
    public slots:
        void onDoubleClick(QModelIndex index);
        void onProcessError(QProcess::ProcessError);
    private:
        void setup();
        void fillWithSavedProjectsData();

        CProjectModel *_model;
};

#endif // CSAVEDPROJECTSTABLEVIEW_HPP
