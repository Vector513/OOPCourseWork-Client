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
    explicit MainWindow(QWidget *parent = nullptr);

signals:
    void findOpponentClicked();

private:
    QLabel *backgroundLabel;  // Для фона с картинкой
    Menu *menu;               // Меню без фона
};

#endif // MAINWINDOW_H
