#include "CMainWindow.hpp"
#include "ProjectXmlContentHandler.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    /*QApplication app(argc, argv);
    CMainWindow w;
    w.show();

    return app.exec();*/

    QXmlSimpleReader *parser     = new QXmlSimpleReader();
    MyXmlContentHandler *handler = new MyXmlContentHandler();

    parser->setContentHandler(handler);

    std::cout<<	"Starting parsing"<< std::endl;

    if (parser->parse(new QXmlInputSource(new QFile("../Projectizer/project.xml")))) {
        std::cout << "Parsed Successfully!" << std::endl;
    } else {
        std::cout << "Parsing Failed..." << std::endl;
    }
}
