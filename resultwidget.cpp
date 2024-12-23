#include "ResultWidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QPainter>
#include <QResizeEvent>

ResultWidget::ResultWidget(MessageHandler* messageHandler, QWidget *parent)
    : MessageHandlerWidget(messageHandler, parent),
    gameResultWidget(new GameResultWidget(messageHandler, this)),
    windowTitleLabel(new QLabel("Результат игры", this)),
    returnToMainMenuButton(new QPushButton("Вернуться в главное меню", this)),
    backgroundPixmap(new QPixmap(":/images/GameWidgetBackground.jpg"))  // Замените на путь к вашему фону
{
    messageHandler->addWidget("ResultWidget", this);
    // Настройка лейбла заголовка
    windowTitleLabel->setAlignment(Qt::AlignCenter);
    windowTitleLabel->setStyleSheet("font-size: 24px; color: white;");

    // Настройка кнопки для возврата в главное меню
    returnToMainMenuButton->setStyleSheet("font-size: 18px; color: white;");
    connect(returnToMainMenuButton, &QPushButton::clicked, this, &ResultWidget::exited);

    // Размещение элементов на экране
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(windowTitleLabel);
    layout->addWidget(gameResultWidget);
    layout->addWidget(returnToMainMenuButton);

    setLayout(layout);
}

void ResultWidget::resetState()
{
    gameResultWidget->resetState();
}

void ResultWidget::start()
{
    gameResultWidget->start();
}

void ResultWidget::onExitClicked()
{
    emit exited();
}

void ResultWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    if (backgroundPixmap && !backgroundPixmap->isNull()) {
        painter.drawPixmap(0, 0, width(), height(), *backgroundPixmap);
    }

    QWidget::paintEvent(event); // Вызов базового класса для корректной отрисовки
}

void ResultWidget::resizeEvent(QResizeEvent* event)
{
    // Можно перерасчитать расположение элементов в зависимости от размеров окна
    QWidget::resizeEvent(event);
}

void ResultWidget::processData(QByteArray& data)
{

}
