#include "MessageHandlerWidget.h"
#include "MessageHandler.h"
#include <QDebug>

MessageHandlerWidget::MessageHandlerWidget(MessageHandler* otherMessageHandler, QWidget *parent)
    : QWidget(parent), messageHandler(otherMessageHandler)
{}

void MessageHandlerWidget::sendData(const QByteArray& data)
{
    if (messageHandler) {
        messageHandler->sendData(data);
    } else {
        qWarning() << "Ошибка: MessageHandler не инициализирован";
    }
}

void MessageHandlerWidget::onDataReceived(QByteArray& data)
{
    processData(data);
}
