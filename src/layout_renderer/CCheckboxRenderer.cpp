#include "CCheckboxRenderer.hpp"

#include <QLayout>
#include <QCheckBox>

CCheckboxRenderer::CCheckboxRenderer(COptionCheckbox *option) : ARenderer(option) { }

/*
 * Czy obiekt bez przypisanego rodzica nie powoduje czasem wycieków pamięci?
 * Jak wykorzystać OOP dla problemu renderowania layoutu?
 */

QHBoxLayout *CCheckboxRenderer::render() {
    auto layout = new QHBoxLayout();
    layout->addWidget(new QCheckBox(this->_option->_name));
    return layout;
}
