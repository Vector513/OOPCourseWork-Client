#ifndef GAMEINFOWIDGET_H
#define GAMEINFOWIDGET_H

#include "MessageHandlerWidget.h"
#include "MessageHandler.h"

#include <QLabel>

class GameInfoWidget : public MessageHandlerWidget
{
    Q_OBJECT

public:
    explicit GameInfoWidget(MessageHandler* messageHandler, QWidget *parent = nullptr);

    void resetState() override;
    void start() override;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QLabel* widgetTitle;
    QLabel* coinsLabel;
    QLabel* movesLeftForYouLabel;
    QLabel* movesLeftForOpponentLabel;
    QLabel* isOpponentLootedLabel;
    QLabel* canMakeMoveLabel;

    void resizeEvent(QResizeEvent* event) override;
    void processData(QByteArray& data) override;
};

#endif // MENUWIDGET_H
