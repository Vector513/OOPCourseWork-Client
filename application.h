#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>
#include <QStackedWidget>
#include "TcpClient.h"
#include "MainWindow.h"
#include "OpponentSearchWindow.h"
#include "GameWindow.h"

class Application : public QWidget {
    Q_OBJECT

public:
    explicit Application(TcpClient* otherTcpClient, QWidget *parent = nullptr);

private:
    void setupLayout();
    void setupConnections();

private slots:
    void onMessageReceived(const QString& message);

    void onFindOpponent();
    void onSearchCanceled();
    void onStartTmpGame();

private:
    TcpClient *tcpClient;

    QStackedWidget *stackedWidget;
    MainWindow *mainWindow;
    OpponentSearchWindow *opponentSearchWindow;
    GameWindow *gameWindow;
};

#endif // APPLICATION_H
