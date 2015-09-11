#ifndef CNEWPROJECTDIALOG_HPP
#define CNEWPROJECTDIALOG_HPP

#include <QMainWindow>
#include <QItemSelection>

class QStandardItem;
class QKeyEvent;

namespace Ui {
    class NewProjectWindow;
}

class CNewProjectWindow : public QMainWindow {
    Q_OBJECT
    public:
       CNewProjectWindow(QString const& directory = "", QWidget *parent = 0);
    private slots:
       void createNewProject();
       void buildTemplateOptions(const QItemSelection& selected, const QItemSelection& deselected);
    private:
        void keyPressEvent(QKeyEvent *event);
        QList<QStandardItem *> prepareRow(const QString &text);

        Ui::NewProjectWindow *ui;
        QString _directory;
};

#endif // CNEWPROJECTDIALOG_HPP
