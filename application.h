#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>
#include <QStackedWidget>
#include "MainWindow.h"
#include "OpponentSearchWindow.h"
#include "GameWindow.h"

class Application : public QWidget {
    Q_OBJECT

public:
    explicit Application(QWidget *parent = nullptr);

private:
    void setupLayout();
    void setupConnections();

private slots:
    void onFindOpponent();
    void onSearchCanceled();
    void onStartTmpGame();

private:
    QStackedWidget *stackedWidget; // Контейнер для переключаемых окон
    MainWindow *mainWindow;
    OpponentSearchWindow *opponentSearchWindow;
    GameWindow *gameWindow;
};

#endif // APPLICATION_H
