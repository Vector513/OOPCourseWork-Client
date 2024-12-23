#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "TcpClient.h"
#include "MessageHandlerWidget.h"

#include <QObject>
#include <QMap>

class MessageHandlerWrapper;

class MessageHandler : public QObject
{
    Q_OBJECT
public:
    explicit MessageHandler(QObject *parent = nullptr);

    void addWidget(QString widgetName, MessageHandlerWidget* widget);
    bool connectToServer(const QString &host, quint16 port);
    void disconnectFromServer();
    void sendData(const QByteArray& data);

signals:
    void dataReceived(QByteArray& data);
    void disconnected();

private slots:
    void onDataReceived(QByteArray& data);

private:
    QMap<QString, MessageHandlerWidget*> widgetMap;
    TcpClient tcpClient;

    MessageHandlerWidget* selectWidgetBasedOnData(QByteArray& data);
    void processData(QByteArray& data);
};

#endif // MESSAGEHANDLER_H
