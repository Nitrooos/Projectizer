#include "CLayoutManager.hpp"

#include <QWidget>
#include <QLayout>

CLayoutManager::CLayoutManager(QWidget *main_layout_widget, QVBoxLayout *main_layout)
    : _main_layout_widget(main_layout_widget), _main_layout(main_layout) { }

void CLayoutManager::addLayoutWithWidgets(QList<QWidget*> widgets_list) {
    auto sub_layout = new QHBoxLayout();

    for (auto widget : widgets_list) {
        sub_layout->addWidget(widget);
    }

    this->_widget_list += widgets_list;
    this->_sub_layouts.push_back(sub_layout);
    this->_main_layout->addLayout(sub_layout);
}

void CLayoutManager::clearMainLayout() {
    for (QHBoxLayout *sub_layout : this->_sub_layouts) {
        this->_main_layout->removeItem(sub_layout);
    }

    this->_sub_layouts.clear();

    for (auto widget : this->_widget_list) {
        delete widget;
    }

    this->_widget_list.clear();
}
