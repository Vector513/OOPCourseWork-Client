#ifndef MENU_H
#define MENU_H

#include "TcpClient.h"

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class Menu : public QWidget
{
    Q_OBJECT
public:
    explicit Menu(TcpClient *otherTcpClient, QWidget *parent = nullptr);

signals:
    void findOpponentClicked(); // Сигнал, который будет испущен при нажатии кнопки "Найти соперника"

private:
    TcpClient *tcpClient;
    QString host;
    quint16 port;

    QPushButton *findOpponentButton;

private slots:
    void onFindOpponentClicked();
};

#endif // MENU_H
