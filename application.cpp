#include "Application.h"
#include <QVBoxLayout>

Application::Application(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Главное окно");
    setMinimumSize(800, 600);

    setupLayout();
    setupConnections();
}

void Application::setupLayout() {
    // Создаем основное окно с вертикальным layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Создаем QStackedWidget для переключения между окнами
    stackedWidget = new QStackedWidget(this);

    // Инициализация меню и окна поиска соперника
    mainWindow = new MainWindow(this);
    opponentSearchWindow = new OpponentSearchWindow(this);
    gameWindow = new GameWindow(this);

    // Добавляем оба окна в QStackedWidget
    stackedWidget->addWidget(mainWindow);               // Главное меню
    stackedWidget->addWidget(opponentSearchWindow); // Окно поиска соперника
    stackedWidget->addWidget(gameWindow);

    // Устанавливаем первый виджет в качестве видимого
    stackedWidget->setCurrentIndex(0); // Индекс 0 - Главное меню

    // Добавляем QStackedWidget в layout
    mainLayout->addWidget(stackedWidget);
    setLayout(mainLayout);
}

void Application::setupConnections() {
    // Подключаем сигнал кнопки "Найти соперника" к слоту
    connect(mainWindow, &MainWindow::findOpponentClicked, this, &Application::onFindOpponent);

    // Подключаем сигнал отмены поиска соперника
    connect(opponentSearchWindow, &OpponentSearchWindow::searchCanceled, this, &Application::onSearchCanceled);
    connect(gameWindow, &GameWindow::returnToMenu, this, &Application::onSearchCanceled);
    connect(opponentSearchWindow, &OpponentSearchWindow::startTmpGame, this, &Application::onStartTmpGame);
}

void Application::onFindOpponent() {
    // Переключаем на окно поиска соперника
    stackedWidget->setCurrentIndex(1); // Индекс 1 - Окно поиска соперника
}

void Application::onSearchCanceled() {
    // Возвращаемся в главное меню
    stackedWidget->setCurrentIndex(0); // Индекс 0 - Главное меню
}

void Application::onStartTmpGame() {
    stackedWidget->setCurrentIndex(2);
}
