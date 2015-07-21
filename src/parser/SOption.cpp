#include "SOption.hpp"

const QMap<QString, SOption::EType> SOption::mapping = {
    {"checkbox", SOption::EType::CHECKBOX},
    {"text", SOption::EType::TEXT},
    {"radio", SOption::EType::RADIO},
    {"selectbox", SOption::EType::SELECT}
};

SOption *SOption::getOptionPerType(const QString &type_name) {
    if (SOption::mapping.find(type_name) != SOption::mapping.end()) {
        EType type = SOption::mapping[type_name];
        switch (type) {
            case EType::CHECKBOX:
                return new SOptionCheckbox();
            case EType::TEXT:
                return new SOptionTextInput();
            case EType::RADIO:
                return new SOptionRadioGroup();
            case EType::SELECT:
                return new SOptionSelectBox();
        }
    }
    return nullptr;
}
