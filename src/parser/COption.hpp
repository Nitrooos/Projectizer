#ifndef COPTION_HPP
#define COPTION_HPP

#include <QDomNode>
#include <QMap>
#include <QString>

class CValue {
    public:
        CValue(QString id, QString label, bool is_default)
            : _id(id), _label(label), _is_default(is_default) { }
        QString print() const;
    private:
        QString _id, _label;
        bool _is_default;
};

class COption {
    public:
        static COption *getOptionPerType(const QString &type);
        virtual void fill(const QDomNode &node);
        virtual QString print() const;
    protected:
        enum EType { CHECKBOX, TEXT, RADIO, SELECT };
        static const QMap<QString, EType> mapping;

        QString _name;
};

    class COptionCheckbox : public COption {
        public:
            virtual void fill(const QDomNode &node);
            virtual QString print() const;
        protected:
            QString _label;
            bool _is_checked;
    };

    class COptionTextInput : public COption {

    };

    class COptionSelectable : public COption {
        public:
            virtual void fill(const QDomNode &node);
            virtual QString print() const;
        protected:
            void fillValue(const QDomNode &node);
            QMap<QString, CValue> _values;
    };

        class COptionRadioGroup : public COptionSelectable {

        };

        class COptionSelectBox : public COptionSelectable {

        };

#endif // COPTION_HPP
