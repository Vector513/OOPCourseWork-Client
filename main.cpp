#include <QApplication>
#include <QStyleFactory>
#include "Application.h"
#include "TcpClient.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TcpClient tcpClient;
    Application application(&tcpClient);

    application.show();
    return app.exec();
}
