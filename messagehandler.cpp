#include "MessageHandler.h"

#include <QDebug>

MessageHandler::MessageHandler(QObject *parent)
    : QObject(parent), tcpClient(this)
{
    connect(&tcpClient, &TcpClient::dataReceived, this, &MessageHandler::onDataReceived);
    connect(&tcpClient, &TcpClient::disconnected, this, &MessageHandler::disconnected);
}

void MessageHandler::addWidget(QString widgetName, MessageHandlerWidget* widget)
{
    if (!widgetName.isEmpty() && widget) {
        widgetMap.insert(widgetName, widget);
    } else {
        qWarning() << "Не удалось добавить виджет: неверные данные.";
    }
}

bool MessageHandler::connectToServer(const QString &host, quint16 port)
{
    return tcpClient.connectToServer(host, port);
}

void MessageHandler::disconnectFromServer()
{
    tcpClient.disconnectFromServer();
}

void MessageHandler::sendData(const QByteArray& data)
{
    if (!data.isEmpty()) {
        tcpClient.sendData(data);
    } else {
        qWarning() << "Попытка отправить пустые данные.";
    }
}

void MessageHandler::onDataReceived(QByteArray& data)
{
    processData(data);
}

MessageHandlerWidget* MessageHandler::selectWidgetBasedOnData(QByteArray& data)
{
    int spaceIndex = data.indexOf(' ');

    QByteArray firstWord = (spaceIndex == -1) ? data : data.left(spaceIndex);
    data = (spaceIndex == -1) ? QByteArray() : data.mid(spaceIndex + 1);

    QString key = QString::fromUtf8(firstWord);

    return widgetMap.value(key, nullptr);
}

void MessageHandler::processData(QByteArray& data)
{
    qDebug() << "Обработка данных: " << data;

    // Разделяем данные по разделителю ";"
    QList<QByteArray> messages = data.split(';');

    for (QByteArray& message : messages) {
        // Убираем возможный пробел в конце каждого сообщения, если он есть
        message = message.trimmed();

        if (!message.isEmpty()) {
            // Обрабатываем каждое сообщение
            MessageHandlerWidget* widget = selectWidgetBasedOnData(message);
            if (widget) {
                widget->onDataReceived(message);
            }
        }
    }
}

