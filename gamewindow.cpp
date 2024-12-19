#include "GameWindow.h"
#include <QGridLayout>
#include <QTime>
#include <QLabel>
#include <QPushButton>

GameWindow::GameWindow(TcpClient* otherTcpClient, QWidget *parent)
    : QWidget(parent)
    , tcpClient(otherTcpClient)
    , seconds(0)
{
    setWindowTitle("Окно игры");
    setMinimumSize(800, 600);

    // Создаем макет
    QGridLayout *gridLayout = new QGridLayout(this);

    QLabel *gameTitle = new QLabel("Игровое окно");
    gameTitle->setAlignment(Qt::AlignCenter);
    gameTitle->setStyleSheet("font-size: 20px; font-weight: bold;");
    gridLayout->addWidget(gameTitle, 0, 0, 1, 3);

    // Инициализация игрового поля
    gameField = new GameField(tcpClient, this);
    gridLayout->addWidget(gameField, 1, 0, 3, 3);

    // Создаем лейблы
    scoreLabel = new QLabel("Счет: 0");
    scoreLabel->setStyleSheet("font-size: 16px;");
    gridLayout->addWidget(scoreLabel, 1, 3);

    turnLabel = new QLabel("Ход: 1");
    turnLabel->setStyleSheet("font-size: 16px;");
    gridLayout->addWidget(turnLabel, 2, 3);

    timeLabel = new QLabel("Время: 00:00");
    timeLabel->setStyleSheet("font-size: 16px;");
    gridLayout->addWidget(timeLabel, 3, 3);

    // Кнопки
    exitButton = new QPushButton("В главное меню");
    exitButton->setStyleSheet("background-color: #e74c3c; color: white; padding: 10px; font-size: 16px;");
    gridLayout->addWidget(exitButton, 4, 0, 1, 4);

    endTurnButton = new QPushButton("Закончить ходы");
    endTurnButton->setStyleSheet("background-color: #3498db; color: white; padding: 10px; font-size: 16px;");
    gridLayout->addWidget(endTurnButton, 5, 0, 1, 2);

    continueButton = new QPushButton("Продолжить");
    continueButton->setStyleSheet("background-color: #2ecc71; color: white; padding: 10px; font-size: 16px;");
    gridLayout->addWidget(continueButton, 5, 2, 1, 2);

    // Создаем таймер
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWindow::updateTimer);
    timer->start(1000);

    // Подключаем сигналы и слоты
    connect(exitButton, &QPushButton::clicked, this, &GameWindow::onExitClicked);
    connect(endTurnButton, &QPushButton::clicked, this, &GameWindow::onEndTurnClicked);
    connect(continueButton, &QPushButton::clicked, this, &GameWindow::onContinueClicked);

    // Подключаем сигнал от игрового поля
    connect(gameField, &GameField::goldBoxClicked, this, &GameWindow::onGoldBoxClicked);

    setLayout(gridLayout);
}

void GameWindow::updateTimer() {
    seconds++;

    QTime time(0, 0);
    time = time.addSecs(seconds);

    timeLabel->setText("Время: " + time.toString("mm:ss"));
}

void GameWindow::onEndTurnClicked() {
    tcpClient->sendData("finalturn");
    qDebug() << "Ход завершен!";
}

void GameWindow::onContinueClicked() {
    tcpClient->sendData("continue");
    qDebug() << "Ход продолжается!";
}

void GameWindow::onExitClicked() {
    tcpClient->disconnectFromServer();
    emit returnToMenu();
}

void GameWindow::onGoldBoxClicked(int index) {
    qDebug() << "Ящик с золотом с индексом" << index << "был открыт!";
}
