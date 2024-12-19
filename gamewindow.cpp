#include "GameWindow.h"
#include <QGridLayout>
#include <QTime>
#include <QLabel>

GameWindow::GameWindow(QWidget *parent) : QWidget(parent), seconds(0) {
    setWindowTitle("Окно игры");
    setMinimumSize(800, 600);

    // Создаем layout
    QGridLayout *gridLayout = new QGridLayout(this);

    // Заголовок для игры
    QLabel *gameTitle = new QLabel("Игровое окно");
    gameTitle->setAlignment(Qt::AlignCenter);
    gameTitle->setStyleSheet("font-size: 20px; font-weight: bold;");
    gridLayout->addWidget(gameTitle, 0, 0, 1, 3);  // Заголовок на весь верхний ряд

    // Игровое поле
    gameField = new GameField(this);
    gridLayout->addWidget(gameField, 1, 0, 3, 3);  // Игровое поле на весь основной контент

    // Окно счета
    scoreLabel = new QLabel("Счет: 0");
    scoreLabel->setStyleSheet("font-size: 16px;");
    gridLayout->addWidget(scoreLabel, 1, 3);

    // Окно номера хода
    turnLabel = new QLabel("Ход: 1");
    turnLabel->setStyleSheet("font-size: 16px;");
    gridLayout->addWidget(turnLabel, 2, 3);

    // Таймер игры
    timeLabel = new QLabel("Время: 00:00");
    timeLabel->setStyleSheet("font-size: 16px;");
    gridLayout->addWidget(timeLabel, 3, 3);

    exitButton = new QPushButton("В главное меню");
    exitButton->setStyleSheet("background-color: #e74c3c; color: white; padding: 10px; font-size: 16px;");
    gridLayout->addWidget(exitButton, 4, 0, 1, 4);

    // Настройка таймера
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWindow::updateTimer);
    timer->start(1000);  // Таймер обновляется каждую секунду

    setLayout(gridLayout);

    // Подключаем сигнал для открытия ящика с золотом
    connect(gameField, &GameField::goldBoxClicked, this, &GameWindow::onGoldBoxClicked);
    connect(exitButton, &QPushButton::clicked, this, &GameWindow::onExitClicked);
}

void GameWindow::updateTimer() {
    seconds++;  // Увеличиваем счетчик времени

    QTime time(0, 0);
    time = time.addSecs(seconds);  // Преобразуем в формат времени

    timeLabel->setText("Время: " + time.toString("mm:ss"));
}

void GameWindow::onGoldBoxClicked(int index) {
    // Обрабатываем клик по ящику с золотом (например, увеличиваем счет)
    // Логика обработки открытия ящика с золотом
    qDebug() << "Ящик с золотом с индексом" << index << "был открыт!";
}

void GameWindow::onExitClicked() {
    // Отправляем сигнал для возврата в меню
    emit returnToMenu();
}

/*
#include "GameWindow.h"

GameWindow::GameWindow(QWidget *parent) : QWidget(parent) {
    // Применяем стили к окну игры
    setStyleSheet(R"(
        background-color: #ffffff;
        font-family: 'Helvetica', sans-serif;
        font-size: 16px;
        color: #333;
        padding: 15px;
    )");

    QVBoxLayout *layout = new QVBoxLayout(this);

    // Заголовок
    QLabel *label = new QLabel("Игра началась!");
    label->setStyleSheet("font-size: 20px; font-weight: bold; color: #2C3E50;");
    QPushButton *backButton = new QPushButton("Вернуться к настройкам");
    backButton->setStyleSheet(R"(
        background-color: #f39c12;
        color: white;
        padding: 10px;
        border-radius: 5px;
        font-size: 16px;
    )");

    layout->addWidget(label);
    layout->addWidget(backButton);
    setLayout(layout);

    // Подключаем сигнал для возврата в меню настроек
    connect(backButton, &QPushButton::clicked, this, &GameWindow::returnToSettings);
}
*/
