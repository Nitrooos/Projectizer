#ifndef COPTION_HPP
#define COPTION_HPP

#include <QDomNode>
#include <QMap>
#include <QString>

class QHBoxLayout;
class QWidget;

struct CValue {
    public:
        CValue(QString id, QString label, bool is_default)
            : _id(id), _label(label), _is_default(is_default) { }
        QString print() const;

        QString _id, _label;
        bool _is_default;
};

class COption {
    public:
        static COption *getOptionPerType(const QString &type);
        virtual void fill(const QDomNode &node);
        virtual QList<QWidget*> render(QWidget *parent = nullptr) const;
        virtual QString print() const;
    protected:
        enum EType { CHECKBOX, TEXT, RADIO, SELECT };
        static const QMap<QString, EType> mapping;

        QString _id, _name;
};

    class COptionCheckbox : public COption {
        public:
            virtual void fill(const QDomNode &node);
            virtual QList<QWidget*> render(QWidget *parent = nullptr) const;
            virtual QString print() const;
        protected:
            QString _label;
            bool _is_checked;
    };

    class COptionTextInput : public COption {
        public:
            virtual QList<QWidget*> render(QWidget *parent = nullptr) const;
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
            virtual QList<QWidget*> render(QWidget *parent = nullptr) const;
        };

        class COptionSelectBox : public COptionSelectable {
            virtual QList<QWidget*> render(QWidget *parent = nullptr) const;
        };

#endif // COPTION_HPP
