#ifndef SOPTION_HPP
#define SOPTION_HPP

#include <QMap>
#include <QString>
#include <QList>

struct SValue {
    QString _id, _label;
    bool _is_default;
};

struct SOption {
    enum EType {
        CHECKBOX, TEXT, RADIO, SELECT
    };
    static const QMap<QString, EType> mapping;

    static SOption *getOptionPerType(const QString &type);


    QString _name;
};

    struct SOptionCheckbox : SOption {
        QString _label;
        bool _is_checked;
    };

    struct SOptionTextInput : SOption {

    };

    struct SOptionSelectable : SOption {
        QList<SValue> _values;
    };

        struct SOptionRadioGroup : SOptionSelectable {

        };

        struct SOptionSelectBox : SOptionSelectable {

        };

#endif // SOPTION_HPP
