#include "GameWidget.h"
#include "GameFieldWidget.h"
#include "GameInfoWidget.h"

#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <QHBoxLayout>

GameWidget::GameWidget(MessageHandler* messageHandler, QWidget* parent)
    : MessageHandlerWidget(messageHandler, parent),
    gameFieldWidget(new GameFieldWidget(messageHandler, this)),
    gameInfoWidget(new GameInfoWidget(messageHandler, this)),
    backgroundPixmap(new QPixmap(":/GameWidgetBackground.jpg")),
    windowTitleLabel(new QLabel("Игра", this)),
    returnToMainMenuButton(new QPushButton("В главное меню", this)),
    timerLabel(new QLabel("00:00", this)),
    finishButton(new QPushButton("Взять и закончить", this)),
    continueButton(new QPushButton("Продолжить", this)),
    timer(new QTimer(this)),
    elapsedTime(0)
{
    messageHandler->addWidget("GameWidget", this);

    windowTitleLabel->setAlignment(Qt::AlignCenter);
    windowTitleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: white;");


    timerLabel->setAlignment(Qt::AlignRight);
    timerLabel->setStyleSheet("font-size: 14px; color: white;");

    connect(timer, &QTimer::timeout, this, [this]() {
        elapsedTime++;
        int minutes = elapsedTime / 60;
        int seconds = elapsedTime % 60;
        timerLabel->setText(QString::asprintf("%02d:%02d", minutes, seconds));
    });

    // Кнопки
    returnToMainMenuButton->setStyleSheet("background-color: #007bff; color: white;");
    finishButton->setStyleSheet("background-color: #28a745; color: white;");
    continueButton->setStyleSheet("background-color: #ffc107; color: white;");

    connect(returnToMainMenuButton, &QPushButton::clicked, this, &GameWidget::onExitClicked);
    connect(finishButton, &QPushButton::clicked, this, &GameWidget::onFinishClicked);
    connect(continueButton, &QPushButton::clicked, this, &GameWidget::onContinueClicked);

    // Запускаем таймер
    timer->start(1000);  // Обновляется каждую секунду
}

void GameWidget::resetState()
{
    gameFieldWidget->resetState();
    gameInfoWidget->resetState();
    elapsedTime = 0;
    timerLabel->setText("00:00");
}

void GameWidget::start()
{
    // Старт игры
    gameFieldWidget->start();
    gameInfoWidget->start();
}

void GameWidget::onExitClicked()
{
    messageHandler->disconnectFromServer();
    emit disconnected();
}

void GameWidget::onFinishClicked()
{
    messageHandler->sendData("GameSession Finish");
}

void GameWidget::onContinueClicked()
{
    messageHandler->sendData("GameSession Continue");
}

void GameWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    // Рисуем фон
    if (backgroundPixmap) {
        painter.drawPixmap(0, 0, *backgroundPixmap);
    }

    QWidget::paintEvent(event);
}

void GameWidget::resizeEvent(QResizeEvent* event)
{
    // Устанавливаем геометрию виджетов
    int width = this->width();
    int height = this->height();

    windowTitleLabel->setGeometry(0, 0, width, 40);
    gameFieldWidget->setGeometry(0, 40, width * 0.7, height - 140);  // 70% ширины
    gameInfoWidget->setGeometry(width * 0.7, 40, width * 0.3, height - 140);  // 30% ширины

    returnToMainMenuButton->setGeometry(10, 10, 150, 30);
    timerLabel->setGeometry(width - 100, 10, 90, 30);
    finishButton->setGeometry(width / 2 - 100, height - 80, 200, 40);
    continueButton->setGeometry(width / 2 - 100, height - 120, 200, 40);

    QWidget::resizeEvent(event);
}

void GameWidget::processData(QByteArray& data)
{
    // Обработка данных от MessageHandler
    // В зависимости от данных можно обновить состояние игры, например:
    // Если данные содержат информацию о текущем счете, изменим его на соответствующие лейблы.
    // Здесь можно обрабатывать другие данные, например, информацию о ходе игры.
}
