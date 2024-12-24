#include "GameResultWidget.h"
#include <QPainter>
#include <QTimer>
#include <QVBoxLayout>

GameResultWidget::GameResultWidget(MessageHandler* messageHandler, QWidget* parent)
    : MessageHandlerWidget(messageHandler, parent),
    statusLabel(new QLabel(this)),
    infoLabel(new QLabel(this)),
    timePassedLabel(new QLabel(this))
{
    messageHandler->addWidget("GameResultWidget", this);

    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: green;");

    infoLabel->setAlignment(Qt::AlignCenter);
    infoLabel->setStyleSheet("font-size: 14px; color: white;");

    timePassedLabel->setAlignment(Qt::AlignCenter);
    timePassedLabel->setStyleSheet("font-size: 12px; color: white;");

    statusLabel->setText("Вы ?");
    infoLabel->setText("Вы ?");
    timePassedLabel->setText("Партия заняла 0м 0с");
}

void GameResultWidget::resetState()
{
    statusLabel->clear();
    infoLabel->clear();
    timePassedLabel->clear();
}

void GameResultWidget::start()
{
    // Старт игры, если нужно
}

void GameResultWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    // Рисуем фон
    painter.setBrush(QColor(0, 0, 0, 100));  // Полупрозрачный черный фон
    painter.drawRect(this->rect());  // Покрыть весь виджет

    // Отображаем текст
    QWidget::paintEvent(event);
}

void GameResultWidget::resizeEvent(QResizeEvent* event)
{
    int width = this->width();
    int height = this->height();

    // Располагаем лейблы
    statusLabel->setGeometry(0, height / 4, width, 40);  // Пример: в верхней части
    infoLabel->setGeometry(0, height / 2, width, 40);  // Пример: в центре
    timePassedLabel->setGeometry(0, height * 3 / 4, width, 40);  // Пример: внизу

    QWidget::resizeEvent(event);
}

void GameResultWidget::processData(QByteArray& data)
{
    QList<QByteArray> parts = data.split(' ');

    if (parts[0] == "Winner") {
        if (parts[1] == "Disconnected") {
            statusLabel->setText("Победа!");
            infoLabel->setText("Соперник отключился");
            timePassedLabel->setText(QString("Партия заняла %1м %2с").arg(parts[2].toInt()).arg(parts[3].toInt()));
        }
        else {
            int coinDifference = parts[1].toInt();
            int minutes = parts[2].toInt();
            int seconds = parts[3].toInt();

            statusLabel->setText("Победа!");
            infoLabel->setText(QString("Вы набрали на %1 монеты больше чем соперник").arg(coinDifference));
            timePassedLabel->setText(QString("Партия заняла %1м %2с").arg(minutes).arg(seconds));
        }
    } else if (data.startsWith("Loser")) {
        int coinDifference = parts[1].toInt();
        int minutes = parts[2].toInt();
        int seconds = parts[3].toInt();

        statusLabel->setText("Поражение!");
        infoLabel->setText(QString("Вы набрали на %1 монеты меньше чем соперник").arg(coinDifference));
        timePassedLabel->setText(QString("Партия заняла %1м %2с").arg(minutes).arg(seconds));
    } else if (data.startsWith("Draw")) {
        int minutes = parts[1].toInt();
        int seconds = parts[2].toInt();

        statusLabel->setText("Ничья!");
        infoLabel->setText("Соперник набрал такое же количество монет");
        timePassedLabel->setText(QString("Партия заняла %1м %2с").arg(minutes).arg(seconds));
    }
}

