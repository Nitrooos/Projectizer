#ifndef CSAVEDPROJECTSTABLEVIEW_HPP
#define CSAVEDPROJECTSTABLEVIEW_HPP

#include "src/model/CProjectModel.hpp"
#include <QProcess>
#include <QTableView>
#include <QKeyEvent>

class CSavedProjectsTableView : public QTableView {
    Q_OBJECT
    public:
        CSavedProjectsTableView(QWidget *parent);

        int getSelectedRowIndex() const;
        CProjectModel *model() const;
    public slots:
        void handleProcessError(QProcess::ProcessError);
        void runProjectScript(QModelIndex index);
        void removeSavedProjectXMLFile();
    signals:
        void scriptRunSuccessfully();
    private:
        void setup();
        void fillWithSavedProjectsData();
        void keyPressEvent(QKeyEvent *event);

        CProjectModel *_model;
};

#endif // CSAVEDPROJECTSTABLEVIEW_HPP
