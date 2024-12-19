#ifndef OPPONENTSEARCHWINDOW_H
#define OPPONENTSEARCHWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
#include "TcpClient.h"

class OpponentSearchWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OpponentSearchWindow(TcpClient* otherTcpClient, QWidget *parent = nullptr);

    void startWork();    // Запуск работы окна
    void resetState();   // Сброс состояния окна

signals:
    void searchCanceled();
    void startTmpGame();

private slots:
    void updateTimer();
    void cancelSearch();
    void onTmpButtonClicked();

private:
    TcpClient* tcpClient;
    QLabel* timerLabel;
    QTimer* timer;
    int elapsedTime;
};

#endif // OPPONENTSEARCHWINDOW_H
