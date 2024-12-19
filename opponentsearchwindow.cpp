#include "OpponentSearchWindow.h"

OpponentSearchWindow::OpponentSearchWindow(TcpClient* otherTcpClient, QWidget *parent)
    : QWidget(parent)
    , tcpClient(otherTcpClient)
    , elapsedTime(0)
{
    setStyleSheet(R"(
        background-color: #2c3e50;
        color: white;
        font-family: 'Arial', sans-serif;
        font-size: 16px;
    )");

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("Поиск соперника...");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; margin-bottom: 20px;");
    layout->addWidget(titleLabel);

    timerLabel = new QLabel("Время поиска: 0 сек");
    timerLabel->setAlignment(Qt::AlignCenter);
    timerLabel->setStyleSheet("font-size: 18px;");
    layout->addWidget(timerLabel);

    QPushButton *cancelButton = new QPushButton("Отменить поиск");
    cancelButton->setObjectName("cancelButton");
    cancelButton->setStyleSheet(R"(
        background-color: #e74c3c;
        color: white;
        padding: 10px;
        border-radius: 5px;
        font-size: 16px;
    )");
    layout->addWidget(cancelButton);

    QPushButton *tmpGameButton = new QPushButton("Перейти к игре");
    tmpGameButton->setObjectName("tmpGameButton");
    tmpGameButton->setStyleSheet(R"(
        background-color: #b4ae56;
        color: white;
        padding: 10px;
        border-radius: 5px;
        font-size: 16px;
    )");
    layout->addWidget(tmpGameButton);

    connect(cancelButton, &QPushButton::clicked, this, &OpponentSearchWindow::cancelSearch);
    connect(tmpGameButton, &QPushButton::clicked, this, &OpponentSearchWindow::onTmpButtonClicked);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &OpponentSearchWindow::updateTimer);

    setLayout(layout);
}

void OpponentSearchWindow::startWork() {
    // Запускаем работу окна
    resetState();       // Устанавливаем начальное состояние
    timer->start(1000); // Запускаем таймер
}

void OpponentSearchWindow::resetState() {
    // Сбрасываем время поиска
    elapsedTime = 0;
    timerLabel->setText("Время поиска: 0 сек");

    // Останавливаем таймер, если он активен
    if (timer->isActive()) {
        timer->stop();
    }

    // Восстанавливаем состояния кнопок
    QPushButton *cancelButton = findChild<QPushButton*>("cancelButton");
    if (cancelButton) {
        cancelButton->setEnabled(true);
    }

    QPushButton *tmpGameButton = findChild<QPushButton*>("tmpGameButton");
    if (tmpGameButton) {
        tmpGameButton->setEnabled(true);
    }

    // Прочие действия по сбросу
    tcpClient->disconnectFromServer();
    qDebug() << "OpponentSearchWindow: Состояние сброшено.";
}

void OpponentSearchWindow::updateTimer() {
    elapsedTime++;
    timerLabel->setText(QString("Время поиска: %1 сек").arg(elapsedTime));
}

void OpponentSearchWindow::cancelSearch() {
    tcpClient->disconnectFromServer();
    timer->stop();
    emit searchCanceled();
}

void OpponentSearchWindow::onTmpButtonClicked() {
    timer->stop();
    emit startTmpGame();
}
