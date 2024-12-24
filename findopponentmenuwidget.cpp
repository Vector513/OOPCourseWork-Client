#include "FindOpponentMenuWidget.h"

#include <QPainter>
#include <QPainterPath>
#include <QTimer>
#include <QFontMetrics>
#include <QDebug>

FindOpponentMenuWidget::FindOpponentMenuWidget(MessageHandler* messageHandler, QWidget* parent)
    : MessageHandlerWidget(messageHandler, parent), timeElapsed(0)
{
    messageHandler->addWidget("FindOpponentMenuWidget", this);

    cancelSearchButton = new QPushButton("Отменить поиск", this);
    cancelSearchButton->setStyleSheet("background-color: #F08E38; border-radius: 10px;");

    connect(cancelSearchButton, &QPushButton::clicked, this, &FindOpponentMenuWidget::onCancelSearchClicked);

    // Инициализация QLabel для отображения времени
    timePassedLabel = new QLabel("Времени прошло: 0с", this);
    timePassedLabel->setStyleSheet("background-color: #63A4E5;");
    timePassedLabel->setAlignment(Qt::AlignCenter);

    // Таймер для обновления времени
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FindOpponentMenuWidget::onTimeout);
}

void FindOpponentMenuWidget::resetState()
{
    timer->stop();
    timeElapsed = 0;
    timePassedLabel->setText("Времени прошло: 0");
    cancelSearchButton->setEnabled(false);
}

void FindOpponentMenuWidget::start()
{
    timeElapsed = 0;
    timer->start(1000);  // Запуск таймера с интервалом в 1 секунду
    cancelSearchButton->setEnabled(true);
}

void FindOpponentMenuWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int cornerRadius = std::min(width(), height()) / 16;  // Радиус закругления
    QPainterPath path;
    path.addRoundedRect(rect(), cornerRadius, cornerRadius);

    painter.setBrush(QColor(191, 150, 88, 100));  // Полупрозрачный черный фон
    painter.drawRect(this->rect());  // Покрыть весь виджет

    QWidget::paintEvent(event);
}

void FindOpponentMenuWidget::onCancelSearchClicked()
{
    messageHandler->disconnectFromServer();
    timer->stop();
    emit disconnected();
}

void FindOpponentMenuWidget::onTimeout()
{
    timeElapsed++;
    timePassedLabel->setText(QString("Времени прошло: %1с").arg(timeElapsed));
}

void FindOpponentMenuWidget::resizeEvent(QResizeEvent* event)
{
    int windowWidth = width();
    int windowHeight = height();

    // Размеры и позиция timePassedLabel
    int labelWidth = windowWidth * 2 / 3; // Ширина как 2 к 3 от ширины виджета
    int labelHeight = windowHeight * 15 / 40; // Высота как 15 к 40 от высоты виджета
    int labelX = (windowWidth - labelWidth) / 2; // Центрирование по горизонтали
    int labelY = windowHeight * 50 / 400; // Расстояние от верхней границы виджета
    timePassedLabel->setGeometry(labelX, labelY, labelWidth, labelHeight);

    // Размеры и позиция cancelSearchButton
    int buttonWidth = windowWidth / 2; // Ширина как половина ширины виджета
    int buttonHeight = windowHeight / 4; // Высота как четверть высоты виджета
    int buttonX = (windowWidth - buttonWidth) / 2; // Центрирование по горизонтали
    int buttonY = windowHeight - (windowHeight / 8) - buttonHeight; // Отступ от нижней границы
    cancelSearchButton->setGeometry(buttonX, buttonY, buttonWidth, buttonHeight);

    // Расчет начального размера шрифта
    int fontSize = buttonHeight / 2; // Исходный размер шрифта — половина высоты кнопки
    QFont font = cancelSearchButton->font();
    font.setPointSize(fontSize);

    QFontMetrics metrics(font);

    // Проверяем текст для кнопки
    int buttonTextWidth = metrics.horizontalAdvance(cancelSearchButton->text());
    if (buttonTextWidth > buttonWidth * 0.9) {
        font.setPointSize(buttonWidth * 0.9 / buttonTextWidth * fontSize);
    }

    // Проверяем текст для лейбла
    int labelTextWidth = metrics.horizontalAdvance(timePassedLabel->text());
    if (labelTextWidth > labelWidth * 0.9) {
        font.setPointSize(labelWidth * 0.9 / labelTextWidth * fontSize);
    }

    // Применяем одинаковый размер шрифта
    cancelSearchButton->setFont(font);
    timePassedLabel->setFont(font);

    QWidget::resizeEvent(event);
}

void FindOpponentMenuWidget::processData(QByteArray& data)
{
    QString message = QString::fromUtf8(data);


}
