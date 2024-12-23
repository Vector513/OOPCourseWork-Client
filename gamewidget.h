#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "MessageHandlerWidget.h"
#include "GameFieldWidget.h"
#include "GameInfoWidget.h"

#include <QLabel>
#include <QPixmap>

class GameWidget : public MessageHandlerWidget
{
    Q_OBJECT

public:
    explicit GameWidget(MessageHandler* messageHandler, QWidget *parent = nullptr);

    void resetState() override;
    void start() override;

protected:
    void paintEvent(QPaintEvent* event) override;

signals:
    void disconnected();

private slots:
    void onExitClicked();
    void onFinishClicked();
    void onContinueClicked();

private:
    GameFieldWidget* gameFieldWidget;
    GameInfoWidget* gameInfoWidget;

    QPixmap* backgroundPixmap;
    QLabel* windowTitleLabel;
    QPushButton* returnToMainMenuButton;
    QLabel* timerLabel;
    QPushButton* finishButton;
    QPushButton* continueButton;
    QTimer* timer;
    int elapsedTime;

    void resizeEvent(QResizeEvent* event) override;
    void processData(QByteArray& data) override;
};

#endif // MAINWIDGET_H
