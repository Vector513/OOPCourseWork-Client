#ifndef GAMERESULTWIDGET_H
#define GAMERESULTWIDGET_H

#include "MessageHandlerWidget.h"
#include "MessageHandler.h"

#include <QLabel>

class GameResultWidget : public MessageHandlerWidget
{
    Q_OBJECT

public:
    explicit GameResultWidget(MessageHandler* messageHandler, QWidget *parent = nullptr);

    void resetState() override;
    void start() override;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QLabel* statusLabel;
    QLabel* infoLabel;
    QLabel* timePassedLabel;

    void resizeEvent(QResizeEvent* event) override;
    void processData(QByteArray& data) override;
};

#endif // MENUWIDGET_H
