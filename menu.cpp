#include "Menu.h"

Menu::Menu(TcpClient *otherTcpClient, QWidget *parent)
    : QWidget(parent)
    , tcpClient(otherTcpClient)
    , host("192.168.31.227")
    , port(10001)
{
    // Устанавливаем общий стиль для окна
    setStyleSheet(R"(
        background-color: #f0f4f7;
        font-family: 'Arial', sans-serif;
        font-size: 14px;
    )");

    // Создаем кнопку "Найти соперника"
    findOpponentButton = new QPushButton("Найти соперника", this);
    findOpponentButton->setStyleSheet(R"(
        background-color: #3498db;
        color: white;
        padding: 10px;
        border-radius: 5px;
        font-size: 16px;
    )");

    // Создаем вертикальный layout и добавляем кнопку
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addStretch(); // Добавляем пространство сверху
    layout->addWidget(findOpponentButton, 0, Qt::AlignCenter); // Центрируем кнопку
    layout->addStretch(); // Добавляем пространство снизу

    setLayout(layout);

    // Подключаем сигнал кнопки к пользовательскому сигналу
    connect(findOpponentButton, &QPushButton::clicked, this, &Menu::findOpponentClicked);
    connect(findOpponentButton, &QPushButton::clicked, this, &Menu::onFindOpponentClicked);
}

void Menu::onFindOpponentClicked()
{
    tcpClient->connectToServer(host, port);
}
