#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include "GameField.h"

class GameWindow : public QWidget {
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);

signals:
    void returnToMenu();

private slots:
    void updateTimer();
    void onExitClicked();
    void onGoldBoxClicked(int index);  // Слот для обработки открытия ящика с золотом

private:
    QLabel *scoreLabel;         // Отображение счета
    QLabel *turnLabel;          // Номер хода
    QLabel *timeLabel;          // Таймер игры
    QTimer *timer;              // Таймер игры
    int seconds;                // Секунды для таймера
    GameField *gameField;       // Игровое поле

    QPushButton *exitButton;
};

#endif // GAMEWINDOW_H





/*
#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

class GameWindow : public QWidget {
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);

signals:
    void returnToSettings();  // Сигнал для возврата в меню настроек
};

#endif // GAMEWINDOW_H
*/
