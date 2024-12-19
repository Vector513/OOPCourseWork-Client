#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "Menu.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(TcpClient *otherTcpClient, QWidget *parent = nullptr);

signals:
    void findOpponentClicked();

private:
    TcpClient *tcpClient;
    QLabel *backgroundLabel;  // Для фона с картинкой
    Menu *menu;               // Меню без фона
};

#endif // MAINWINDOW_H
