#ifndef COPTION_HPP
#define COPTION_HPP

#include <QDomNode>
#include <QMap>
#include <QString>

class QHBoxLayout;
class QVBoxLayout;
class QWidget;

struct CValue {
    public:
        CValue(QString id, QString label, bool is_default)
            : _id(id), _label(label), _is_default(is_default) { }

        QString _id, _label;
        bool _is_default;
};

class COption {
    public:
        static COption *getOptionPerType(const QString &type);
        virtual void fill(const QDomNode &node);
        virtual QList<QWidget*> render(QWidget *parent = nullptr);
        virtual QString value() const = 0;
    protected:
        enum EType { CHECKBOX, TEXT, RADIO, SELECT };
        static const QMap<QString, EType> mapping;

        QString _id, _name;
        QList<QWidget*> _widgets;
};

    class COptionCheckbox : public COption {
        public:
            virtual void fill(const QDomNode &node);
            virtual QList<QWidget*> render(QWidget *parent = nullptr);
            virtual QString value() const;
        protected:
            QString _label;
            bool _is_checked;
    };

    class COptionTextInput : public COption {
        public:
            virtual QList<QWidget*> render(QWidget *parent = nullptr);
    };

    class COptionSelectable : public COption {
        public:
            virtual void fill(const QDomNode &node);
        protected:
            void fillValue(const QDomNode &node);
            QMap<QString, CValue> _values;
    };

        class COptionRadioGroup : public COptionSelectable {
            virtual QList<QWidget*> render(QWidget *parent = nullptr);
        };

        class COptionSelectBox : public COptionSelectable {
            virtual QList<QWidget*> render(QWidget *parent = nullptr);
        };

#endif // COPTION_HPP
