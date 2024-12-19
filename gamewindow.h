#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QPushButton>
#include "GameField.h"
#include "TcpClient.h"

class GameWindow : public QWidget {
    Q_OBJECT

public:
    explicit GameWindow(TcpClient* otherTcpClient, QWidget *parent = nullptr);

signals:
    void returnToMenu();

private slots:
    void updateTimer();
    void onExitClicked();
    void onEndTurnClicked();
    void onContinueClicked();
    void onGoldBoxClicked(int index);

private:
    TcpClient *tcpClient;
    QLabel *scoreLabel;
    QLabel *turnLabel;
    QLabel *timeLabel;
    QTimer *timer;  // Объект для таймера
    int seconds;

    QPushButton *exitButton;
    QPushButton *endTurnButton;
    QPushButton *continueButton;

    GameField *gameField;  // Объект GameField
};

#endif // GAMEWINDOW_H
