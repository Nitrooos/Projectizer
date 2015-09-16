#ifndef CNEWPROJECTDIALOG_HPP
#define CNEWPROJECTDIALOG_HPP

#include "src/new_projects/options_layout/CLayoutManager.hpp"
#include "src/new_projects/model/CProjectTypeModel.hpp"

#include <QMainWindow>
#include <QItemSelection>

class QKeyEvent;

namespace Ui {
    class NewProjectWindow;
}

class CNewProjectWindow : public QMainWindow {
    Q_OBJECT
    public:
       CNewProjectWindow(QString const& directory = "", QWidget *parent = 0);
       ~CNewProjectWindow();
    private slots:
       void createNewProject();
       void buildTemplateOptions(const QItemSelection& selected, const QItemSelection& deselected);
    private:
        void keyPressEvent(QKeyEvent *event);

        Ui::NewProjectWindow *ui;
        CLayoutManager *_layout_manager;
        QString _directory;
        CProjectTypeModel *_model;
};

#endif // CNEWPROJECTDIALOG_HPP
