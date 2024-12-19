#include "GameLobbyWindow.h"
#include <QDebug>

GameLobbyWindow::GameLobbyWindow(QWidget *parent) : QWidget(parent) {
    // Применяем стили
    setStyleSheet(R"(
        background-color: #ecf0f1;
        font-family: 'Verdana', sans-serif;
        font-size: 14px;
        color: #2c3e50;
        padding: 20px;
    )");

    QVBoxLayout *layout = new QVBoxLayout(this);

    // Заголовок
    QLabel *label = new QLabel("Выберите оппонента:");
    label->setStyleSheet("font-size: 18px; font-weight: bold; color: #3498db;");
    layout->addWidget(label);

    // Список доступных игроков (статичный пример)
    QPushButton *playerButton1 = new QPushButton("Игрок 1");
    QPushButton *playerButton2 = new QPushButton("Игрок 2");

    // Стили для кнопок
    playerButton1->setStyleSheet(R"(
        background-color: #3498db;
        color: white;
        padding: 10px;
        border-radius: 5px;
        font-size: 16px;
    )");

    playerButton2->setStyleSheet(R"(
        background-color: #3498db;
        color: white;
        padding: 10px;
        border-radius: 5px;
        font-size: 16px;
    )");

    // Добавляем кнопки на экран
    layout->addWidget(playerButton1);
    layout->addWidget(playerButton2);

    // Кнопка возврата в главное меню
    QPushButton *backButton = new QPushButton("Назад в меню");
    backButton->setStyleSheet(R"(
        background-color: #e74c3c;
        color: white;
        padding: 10px;
        border-radius: 5px;
        font-size: 16px;
    )");

    // Добавляем кнопку возврата в меню
    layout->addWidget(backButton);

    // Подключаем кнопки к слотам
    connect(playerButton1, &QPushButton::clicked, this, &GameLobbyWindow::startNetworkGame);
    connect(playerButton2, &QPushButton::clicked, this, &GameLobbyWindow::startNetworkGame);
    connect(backButton, &QPushButton::clicked, this, &GameLobbyWindow::backToMainMenu);

    setLayout(layout);
}

void GameLobbyWindow::startNetworkGame() {
    // Логика начала сетевой игры
    qDebug() << "Сетевой матч начнется!";
    // Здесь может быть добавлена реализация подключения к серверу или к другому игроку
}

void GameLobbyWindow::backToMainMenu() {
    // Сигнал возврата в главное меню
    emit returnToMainMenu();
}
