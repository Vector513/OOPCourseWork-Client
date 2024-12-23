#include "GameFieldWidget.h"
#include <QPainter>
#include <QResizeEvent>

GameFieldWidget::GameFieldWidget(MessageHandler* messageHandler, QWidget* parent)
    : MessageHandlerWidget(messageHandler, parent)
{
    messageHandler->addWidget("GameField", this);

    setAttribute(Qt::WA_TranslucentBackground);
    setWindowOpacity(0.5);

    for (int i = 0; i < 15; ++i) {
        auto* goldBox = new GoldBoxWidget(messageHandler, i, this);
        goldBoxWidgets.append(goldBox);
    }
}
void GameFieldWidget::resetState()
{
    for (auto* box : goldBoxWidgets) {
        box->resetState();
    }
}

void GameFieldWidget::start()
{
    for (auto* box : goldBoxWidgets) {
        box->start();
    }
}
void GameFieldWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    // Рисуем полупрозрачный фон
    QColor backgroundColor = Qt::darkGreen;
    backgroundColor.setAlpha(128); // 50% прозрачности
    painter.fillRect(this->rect(), backgroundColor);

    QWidget::paintEvent(event);
}

void GameFieldWidget::resizeEvent(QResizeEvent* event)
{
    if (goldBoxWidgets.size() != 15) return;

    // Расположение 5x3
    int rows = 3;
    int cols = 5;

    // Размеры виджета
    int widgetWidth = this->width();
    int widgetHeight = this->height();

    // Размеры ячейки
    int cellWidth = widgetWidth / cols;
    int cellHeight = widgetHeight / rows;

    for (int i = 0; i < goldBoxWidgets.size(); ++i) {
        int row = i / cols; // Номер строки
        int col = i % cols; // Номер столбца

        // Вычисляем положение и размер
        int x = col * cellWidth;
        int y = row * cellHeight;
        goldBoxWidgets[i]->setGeometry(x, y, cellWidth, cellHeight);
    }

    QWidget::resizeEvent(event);
}

void GameFieldWidget::processData(QByteArray& data)
{

}
