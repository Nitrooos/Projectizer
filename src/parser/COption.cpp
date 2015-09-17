#include "COption.hpp"

#include <QWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <QRadioButton>
#include <QButtonGroup>
#include <QComboBox>

const QMap<QString, COption::EType> COption::mapping = {
    {"checkbox", COption::EType::CHECKBOX},
    {"text", COption::EType::TEXT},
    {"radio", COption::EType::RADIO},
    {"selectbox", COption::EType::SELECT}
};

QString CValue::print() const {
    return "      id: " + _id +
           "      label: " + _label +
           "      is_default: " + QString::number(_is_default) + "\n";
}

void COption::fill(const QDomNode &node) {
    if (node.isElement()) {
        QDomNodeList names = node.toElement().elementsByTagName("name");
        if (names.size() > 0) {
            _name = names.item(0).toElement().text();
        }
    }
}

QString COption::print() const {
    return "   name: "  + _name + "\n";
}

COption *COption::getOptionPerType(const QString &type_name) {
    if (COption::mapping.find(type_name) != COption::mapping.end()) {
        EType type = COption::mapping[type_name];
        switch (type) {
            case EType::CHECKBOX:
                return new COptionCheckbox();
            case EType::TEXT:
                return new COptionTextInput();
            case EType::RADIO:
                return new COptionRadioGroup();
            case EType::SELECT:
                return new COptionSelectBox();
        }
    }
    return nullptr;
}

void COptionCheckbox::fill(const QDomNode &node) {
    COption::fill(node);

    if (node.isElement()) {
        QDomNodeList labels = node.toElement().elementsByTagName("label");
        if (labels.size() > 0) {
            _label = labels.item(0).toElement().text();

            QDomAttr is_checked = node.attributes().namedItem("checked").toAttr();
            if (!is_checked.isNull() && is_checked.value() == "true") {
                _is_checked = true;
            } else {
                _is_checked = false;
            }
        }
    }
}

QList<QWidget *> COptionCheckbox::render(QWidget *parent) const {
    QList<QWidget*> list;

    QCheckBox *checkbox = new QCheckBox(this->_label, parent);
    if (this->_is_checked) {
        checkbox->setChecked(true);
    }
    list.push_back(checkbox);

    return list;
}

QString COptionCheckbox::print() const {
    return COption::print() +
           "   label: " + _label + "\n" +
           "   is_checked: " +  QString::number(_is_checked) + "\n";
}

QList<QWidget *> COptionTextInput::render(QWidget *parent) const {
    QList<QWidget*> list{new QLineEdit(parent)};
    return list;
}

void COptionSelectable::fill(const QDomNode &node) {
    COption::fill(node);

    if (node.isElement()) {
        QDomNodeList values_tag = node.toElement().elementsByTagName("values");
        if (values_tag.size() > 0) {
            QDomNodeList values = values_tag.item(0).toElement().elementsByTagName("value");
            for (int i = 0; i < values.size(); ++i) {
                fillValue(values.item(i));
            }
        }
    }
}

void COptionSelectable::fillValue(const QDomNode &node) {
    QDomElement value_element = node.toElement();
    if (value_element.attributes().contains("id")) {
        QString id = value_element.attributes().namedItem("id").toAttr().value(),
                label = value_element.toElement().text();
        bool is_default = false;

        if (value_element.attributes().contains("default") &&
            value_element.attributes().namedItem("default").toAttr().value() == "true")
        {
            is_default = true;
        }

        _values.insert(id, CValue(id, label, is_default));
    }
}

QString COptionSelectable::print() const {
    QString result = COption::print() + "   values:\n";
    for (auto value : _values) {
        result += value.print();
    }
    return result;
}

QList<QWidget *> COptionRadioGroup::render(QWidget *parent) const {
    QList<QWidget*> list;
    QButtonGroup btn_group(parent);
    for (auto radio_option : this->_values) {
        auto radio = new QRadioButton(radio_option._label, parent);
        btn_group.addButton(radio);
        if (radio_option._is_default) {
            radio->setChecked(true);
        }

        list.push_back(radio);
    }

    return list;
}

QList<QWidget *> COptionSelectBox::render(QWidget *parent) const {
    QList<QWidget*> list;
    auto *combo = new QComboBox(parent);
    for (auto combo_option : this->_values) {
        combo->addItem(combo_option._label);
    }
    list.push_back(combo);

    return list;
}
