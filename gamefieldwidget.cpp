#include "GameFieldWidget.h"
#include <QPainter>
#include <QResizeEvent>

GameFieldWidget::GameFieldWidget(MessageHandler* messageHandler, QWidget* parent)
    : MessageHandlerWidget(messageHandler, parent)
{
    messageHandler->addWidget("GameField", this);

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

    painter.setBrush(QColor(0, 0, 0, 100));
    painter.drawRect(this->rect());

    QWidget::paintEvent(event);
}

void GameFieldWidget::resizeEvent(QResizeEvent* event)
{
    if (goldBoxWidgets.size() != 15) return;

    int rows = 3;
    int cols = 5;

    int widgetWidth = this->width();
    int widgetHeight = this->height();

    int cellWidth = widgetWidth / cols;
    int cellHeight = widgetHeight / rows;

    for (int i = 0; i < goldBoxWidgets.size(); ++i) {
        int row = i / cols;
        int col = i % cols;

        int x = col * cellWidth;
        int y = row * cellHeight;
        goldBoxWidgets[i]->setGeometry(x, y, cellWidth, cellHeight);
    }

    QWidget::resizeEvent(event);
}

void GameFieldWidget::processData(QByteArray& data)
{
    return;
}
