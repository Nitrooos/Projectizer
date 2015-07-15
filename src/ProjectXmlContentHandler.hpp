#ifndef MYXMLCONTENTHANDLER_HPP
#define MYXMLCONTENTHANDLER_HPP

#include <QtXml>
#include <iostream>

class MyXmlContentHandler : public QXmlDefaultHandler {
    public:
        MyXmlContentHandler() : QXmlDefaultHandler() { }
        ~MyXmlContentHandler() { }

        bool startElement(const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts );
};

#endif // MYXMLCONTENTHANDLER_HPP
