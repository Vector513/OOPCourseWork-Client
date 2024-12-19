#include "Application.h"
#include <QVBoxLayout>

Application::Application(TcpClient *otherTcpClient, QWidget *parent)
    : QWidget(parent)
    , tcpClient(otherTcpClient)
{
    setWindowTitle("Главное окно");
    setMinimumSize(800, 600);

    setupLayout();
    setupConnections();
}

void Application::setupLayout()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    stackedWidget = new QStackedWidget(this);

    mainWindow = new MainWindow(tcpClient, this);
    opponentSearchWindow = new OpponentSearchWindow(tcpClient, this);
    gameWindow = new GameWindow(tcpClient, this);

    stackedWidget->addWidget(mainWindow);
    stackedWidget->addWidget(opponentSearchWindow);
    stackedWidget->addWidget(gameWindow);

    stackedWidget->setCurrentIndex(0);

    mainLayout->addWidget(stackedWidget);
    setLayout(mainLayout);
}

void Application::setupConnections()
{
    connect(tcpClient, &TcpClient::messageReceived, this, &Application::onMessageReceived);
    connect(tcpClient, &TcpClient::disconnected, this, &Application::onSearchCanceled);
    connect(mainWindow, &MainWindow::findOpponentClicked, this, &Application::onFindOpponent);
    connect(opponentSearchWindow, &OpponentSearchWindow::searchCanceled, this, &Application::onSearchCanceled);
    connect(gameWindow, &GameWindow::returnToMenu, this, &Application::onSearchCanceled);
    connect(opponentSearchWindow, &OpponentSearchWindow::startTmpGame, this, &Application::onStartTmpGame);
}

void Application::onFindOpponent()
{
    stackedWidget->setCurrentWidget(opponentSearchWindow);
    opponentSearchWindow->startWork();
}

void Application::onSearchCanceled()
{
    stackedWidget->setCurrentWidget(mainWindow);
    opponentSearchWindow->resetState();
}

void Application::onMessageReceived(const QString& message)
{
    if (message == "opponentfound") {
        onStartTmpGame();
    }
}

void Application::onStartTmpGame() {
    stackedWidget->setCurrentWidget(gameWindow);
}
