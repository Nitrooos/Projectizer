#ifndef CLAYOUTMANAGER_HPP
#define CLAYOUTMANAGER_HPP

#include <QList>

class QVBoxLayout;
class QHBoxLayout;
class QWidget;

class CLayoutManager {
    public:
        CLayoutManager(QWidget *main_layout_widget, QVBoxLayout *main_layout);

        void addLayoutWithWidgets(QList<QWidget*> widgets_list);
        void clearMainLayout();
    private:
        QWidget *_main_layout_widget;
        QVBoxLayout *_main_layout;
        QList<QHBoxLayout*> _sub_layouts;
        QList<QWidget*> _widget_list;
};

#endif // CLAYOUTMANAGER_HPP
