#include "OpponentSearchWindow.h"

OpponentSearchWindow::OpponentSearchWindow(QWidget *parent) : QWidget(parent), elapsedTime(0) {
    setStyleSheet(R"(
        background-color: #2c3e50;
        color: white;
        font-family: 'Arial', sans-serif;
        font-size: 16px;
    )");

    // Главный layout окна
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Заголовок
    QLabel *titleLabel = new QLabel("Поиск соперника...");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; margin-bottom: 20px;");
    layout->addWidget(titleLabel);

    // Таймер
    timerLabel = new QLabel("Время поиска: 0 сек");
    timerLabel->setAlignment(Qt::AlignCenter);
    timerLabel->setStyleSheet("font-size: 18px;");
    layout->addWidget(timerLabel);

    // Кнопка отмены
    QPushButton *cancelButton = new QPushButton("Отменить поиск");
    cancelButton->setStyleSheet(R"(
        background-color: #e74c3c;
        color: white;
        padding: 10px;
        border-radius: 5px;
        font-size: 16px;
    )");
    layout->addWidget(cancelButton);

    QPushButton *tmpGameButton = new QPushButton("Перейти к игре");
    cancelButton->setStyleSheet(R"(
        background-color: #b4ae56;
        color: white;
        padding: 10px;
        border-radius: 5px;
        font-size: 16px;
    )");
    layout->addWidget(tmpGameButton);
    // Подключаем кнопку отмены к обработчику
    connect(cancelButton, &QPushButton::clicked, this, &OpponentSearchWindow::cancelSearch);

    // Настройка таймера
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &OpponentSearchWindow::updateTimer);
    timer->start(1000); // Обновляем каждую секунду

    connect(tmpGameButton, &QPushButton::clicked, this, &OpponentSearchWindow::onTmpButtonClicked);

    setLayout(layout);
}

void OpponentSearchWindow::updateTimer() {
    elapsedTime++;
    timerLabel->setText(QString("Время поиска: %1 сек").arg(elapsedTime));
}

void OpponentSearchWindow::cancelSearch() {
    timer->stop();       // Останавливаем таймер
    emit searchCanceled(); // Посылаем сигнал о возврате в меню
}

void OpponentSearchWindow::onTmpButtonClicked() {
    timer->stop();
    emit startTmpGame();
}
