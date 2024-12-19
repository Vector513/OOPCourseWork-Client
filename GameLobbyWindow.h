#ifndef GAMELOBBYWINDOW_H
#define GAMELOBBYWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class GameLobbyWindow : public QWidget {
    Q_OBJECT

public:
    explicit GameLobbyWindow(QWidget *parent = nullptr);

public slots:
    void startNetworkGame();   // Слот для начала сетевой игры
    void backToMainMenu();     // Слот для возврата в главное меню

signals:
    void returnToMainMenu();   // Сигнал для возврата в главное меню
};

#endif // GAMELOBBYWINDOW_H
