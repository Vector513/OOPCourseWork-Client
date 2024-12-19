#include "GameSettingsWindow.h"

GameSettingsWindow::GameSettingsWindow(QWidget *parent) : QWidget(parent) {
    setStyleSheet(R"(
        background-color: #ecf0f1;
        font-family: 'Verdana', sans-serif;
        font-size: 14px;
        color: #2c3e50;
        padding: 20px;
    )");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Настройка количества ящиков
    QGroupBox *boxSettings = new QGroupBox("Количество ящиков");
    QVBoxLayout *boxLayout = new QVBoxLayout(boxSettings);
    QLabel *boxLabel = new QLabel("Выберите количество ящиков (1-15):");
    QSpinBox *boxSpinBox = new QSpinBox;
    boxSpinBox->setRange(1, 15);
    boxSpinBox->setValue(1);
    boxLayout->addWidget(boxLabel);
    boxLayout->addWidget(boxSpinBox);

    // Настройка диапазона монет
    QGroupBox *coinSettings = new QGroupBox("Диапазон монет");
    QVBoxLayout *coinLayout = new QVBoxLayout(coinSettings);
    QLabel *coinLabel = new QLabel("Выберите диапазон монет (0-10):");
    QSpinBox *coinSpinBox = new QSpinBox;
    coinSpinBox->setRange(0, 10);
    coinSpinBox->setValue(0);
    coinLayout->addWidget(coinLabel);
    coinLayout->addWidget(coinSpinBox);

    // Настройка количества ходов
    QGroupBox *movesSettings = new QGroupBox("Количество ходов");
    QVBoxLayout *movesLayout = new QVBoxLayout(movesSettings);
    QLabel *movesLabel = new QLabel("Выберите количество ходов (1-5):");
    QSpinBox *movesSpinBox = new QSpinBox;
    movesSpinBox->setRange(1, 5);
    movesSpinBox->setValue(1);
    movesLayout->addWidget(movesLabel);
    movesLayout->addWidget(movesSpinBox);

    // Кнопка для сетевой игры
    QPushButton *networkGameButton = new QPushButton("Сетевая игра");
    networkGameButton->setStyleSheet(R"(
        background-color: #3498db;
        color: white;
        padding: 10px;
        border-radius: 5px;
        font-size: 16px;
    )");

    // Добавление всех элементов в главный макет
    mainLayout->addWidget(boxSettings);
    mainLayout->addWidget(coinSettings);
    mainLayout->addWidget(movesSettings);
    mainLayout->addWidget(networkGameButton);

    connect(networkGameButton, &QPushButton::clicked, this, &GameSettingsWindow::startNetworkGame);

    setLayout(mainLayout);
}
