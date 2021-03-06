#include "COption.hpp"

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QRadioButton>
#include <QButtonGroup>
#include <QComboBox>
#include <QGroupBox>

const QMap<QString, COption::EType> COption::mapping = {
    {"checkbox", COption::EType::CHECKBOX},
    {"text", COption::EType::TEXT},
    {"radio", COption::EType::RADIO},
    {"selectbox", COption::EType::SELECT}
};

void COption::fill(const QDomNode &node) {
    if (node.isElement()) {
        QDomNodeList names = node.toElement().elementsByTagName("name"),
                     ids =   node.toElement().elementsByTagName("id");
        if (names.size() > 0) {
            _name = names.item(0).toElement().text();
        }
        if (ids.size() > 0) {
            _id = ids.item(0).toElement().text();
        }
    }
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

QList<QWidget*> COption::render(QWidget *parent) {
    this->_widgets.clear();
    if (this->_name != "") {
        this->_widgets.push_back(new QLabel(this->_name, parent));
    }
    return this->_widgets;
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

QList<QWidget *> COptionCheckbox::render(QWidget *parent) {
    this->_widgets = COption::render(parent);

    QCheckBox *checkbox = new QCheckBox(this->_label, parent);
    if (this->_is_checked) {
        checkbox->setChecked(true);
    }
    this->_created_checkbox = checkbox;
    this->_widgets.push_back(checkbox);

    return this->_widgets;
}

QString COptionCheckbox::value() const {
    if (this->_created_checkbox == nullptr) {
        return "";
    }

    QString val = this->_created_checkbox->isChecked() ? "1" : "0";
    return QString("--" + this->_id + "=" + val);
}

QList<QWidget *> COptionTextInput::render(QWidget *parent) {
    this->_widgets = COption::render(parent);

    auto input = new QLineEdit(parent);
    this->_created_input = input;
    this->_widgets.append(input);

    return this->_widgets;
}

QString COptionTextInput::value() const {
    if (this->_created_input == nullptr) {
        return "";
    }

    return QString("--" + this->_id + "=\"" + this->_created_input->text() + "\"");
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

        _values.insert(label, CValue(id, label, is_default));
    }
}

QList<QWidget *> COptionRadioGroup::render(QWidget *parent) {
    this->_widgets = QList<QWidget*>();

    auto container = new QGroupBox(this->_name, parent);
    container->setLayout(new QVBoxLayout(container));
    container->layout()->setContentsMargins(0, 5, 0, 0);

    auto *btn_group = new QButtonGroup(container);
    for (auto radio_option : this->_values) {
        auto radio = new QRadioButton(radio_option._label, container);
        radio->setObjectName(radio_option._id);

        btn_group->addButton(radio);
        container->layout()->addWidget(radio);
        if (radio_option._is_default) {
            radio->setChecked(true);
        }
    }
    this->_created_group = btn_group;
    this->_widgets.push_back(container);

    return this->_widgets;
}

QString COptionRadioGroup::value() const {
    if (this->_created_group == nullptr) {
        return "";
    }

    return QString("--" + this->_id + "=" + this->_created_group->checkedButton()->objectName());
}

QList<QWidget *> COptionSelectBox::render(QWidget *parent) {
    this->_widgets = COption::render(parent);

    auto *combo = new QComboBox(parent);
    for (auto combo_option : this->_values) {
        if (combo_option._is_default) {
            combo->insertItem(0, combo_option._label);
            combo->setCurrentIndex(0);
        } else {
            combo->addItem(combo_option._label);
        }
    }
    this->_created_select = combo;
    this->_widgets.push_back(combo);

    return this->_widgets;
}

QString COptionSelectBox::value() const {
    if (this->_created_select == nullptr) {
        return "";
    }

    QString option_id = this->_values[this->_created_select->currentText()]._id;

    return QString("--" + this->_id + "=" + option_id);
}
