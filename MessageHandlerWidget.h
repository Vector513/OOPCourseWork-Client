#ifndef MESSAGEHANDLERWIDGET_H
#define MESSAGEHANDLERWIDGET_H

#include <QWidget>

class MessageHandler;

class MessageHandlerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MessageHandlerWidget(MessageHandler* otherMessageHandler, QWidget *parent = nullptr);

    void sendData(const QByteArray& data);

    virtual void resetState() = 0;
    virtual void start() = 0;

protected:
    MessageHandler* messageHandler;

public slots:
    void onDataReceived(QByteArray& data);

private:
    virtual void processData(QByteArray& data) = 0;
};

#endif // MESSAGEHANDLERWIDGET_H
