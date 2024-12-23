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
    qDebug() << "Мы в виджеет: " << data;

    if (data.startsWith("Winner")) {
        // Строка "Winner 2 3 40" или "Winner Disconnected 2 23" - разбиение на части
        QList<QByteArray> parts = data.split(' ');

        if (parts.size() == 5) {
            // Обычный случай с победой
            int playerCoins = parts[1].toInt();  // Количество монет игрока
            int opponentCoins = parts[2].toInt(); // Количество монет соперника
            int minutes = parts[3].toInt();       // Минуты
            int seconds = parts[4].toInt();       // Секунды

            // Обновляем статус победы
            statusLabel->setText("Победа!");

            // Обновляем текст для информации о монетах
            int coinDifference = playerCoins - opponentCoins;
            infoLabel->setText(QString("Вы набрали на %1 монеты больше чем соперник").arg(coinDifference));

            // Обновляем текст для времени игры
            timePassedLabel->setText(QString("Партия заняла %1м %2с").arg(minutes).arg(seconds));
        }
        else if (parts.size() == 4 && parts[1] == "Disconnected") {
            // Особый случай: соперник отключился
            statusLabel->setText("Победа!");
            infoLabel->setText("Соперник отключился");
            timePassedLabel->setText(QString("Партия заняла %1м %2с").arg(parts[2].toInt()).arg(parts[3].toInt()));
        }
    } else if (data.startsWith("Loser")) {
        QList<QByteArray> parts = data.split(' ');

        // Получаем данные
        int playerCoins = parts[1].toInt();  // Количество монет игрока
        int opponentCoins = parts[2].toInt(); // Количество монет соперника
        int minutes = parts[3].toInt();       // Минуты
        int seconds = parts[4].toInt();       // Секунды

        // Обновляем статус поражения
        statusLabel->setText("Поражение!");

        // Обновляем текст для информации о монетах
        int coinDifference = playerCoins - opponentCoins;
        infoLabel->setText(QString("Вы набрали на %1 монеты меньше чем соперник").arg(coinDifference));

        // Обновляем текст для времени игры
        timePassedLabel->setText(QString("Партия заняла %1м %2с").arg(minutes).arg(seconds));
    } else if (data.startsWith("Draw")) {
        QList<QByteArray> parts = data.split(' ');

        // Получаем данные
        int playerCoins = parts[1].toInt();  // Количество монет игрока
        int opponentCoins = parts[2].toInt(); // Количество монет соперника
        int minutes = parts[3].toInt();       // Минуты
        int seconds = parts[4].toInt();       // Секунды

        // Обновляем статус ничьей
        statusLabel->setText("Ничья!");

        // Обновляем текст для информации о монетах
        int coinDifference = playerCoins - opponentCoins;
        infoLabel->setText(QString("Соперник также набрал %1 монет").arg(coinDifference));

        // Обновляем текст для времени игры
        timePassedLabel->setText(QString("Партия заняла %1м %2с").arg(minutes).arg(seconds));
    }
}

