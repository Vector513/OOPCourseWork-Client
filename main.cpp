#include "Application.h"
#include "MessageHandler.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QApplication::setStyle("Fusion");

    MessageHandler messageHandler;
    Application application(&messageHandler);
    application.show();
    return a.exec();
}
