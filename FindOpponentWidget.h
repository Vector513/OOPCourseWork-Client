#ifndef FINDOPPONENTWIDGET_H
#define FINDOPPONENTWIDGET_H

#include "MessageHandlerWidget.h"
#include "FindOpponentMenuWidget.h"

#include <QLabel>
#include <QPixmap>

class FindOpponentWidget : public MessageHandlerWidget
{
    Q_OBJECT

public:
    explicit FindOpponentWidget(MessageHandler* messageHandler, QWidget *parent = nullptr);

    void resetState() override;
    void start() override;

protected:
    void paintEvent(QPaintEvent* event) override;

signals:
    void disconnected();

private:
    FindOpponentMenuWidget* menuWidget;
    QPixmap* backgroundPixmap;
    QLabel* windowTitleLabel;
    QLabel* onlinePlayersLabel;
    int onlinePlayers;

    void resizeEvent(QResizeEvent* event) override;
    void processData(QByteArray& data) override;
};

#endif // MAINWIDGET_H
