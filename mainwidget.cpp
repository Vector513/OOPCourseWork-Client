#include "MainWidget.h"

#include <QVBoxLayout>
#include <QPainter>
#include <QFont>

MainWidget::MainWidget(MessageHandler* messageHandler, QWidget *parent)
    : MessageHandlerWidget(messageHandler, parent),
    menuWidget(new MenuWidget(messageHandler, this)),
    windowTitleLabel(new QLabel("Главное меню", this)),
    backgroundPixmap(new QPixmap(":/MainWidgetBackground.jpg"))
{
    messageHandler->addWidget("MainWidget", this);
    setAutoFillBackground(true);

    windowTitleLabel->setAlignment(Qt::AlignCenter);
    windowTitleLabel->setStyleSheet(
        "background-color: #7AE176; "
        "border-radius: 15px; "  // Закругленные углы
        "border: 3px solid #5A8D3C;"  // Рамка
        );

    connect(menuWidget, &MenuWidget::exited, this, &MainWidget::exited);
}

void MainWidget::resetState() {}

void MainWidget::start() {}

void MainWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    if (backgroundPixmap && !backgroundPixmap->isNull()) {
        painter.drawPixmap(0, 0, width(), height(), *backgroundPixmap);
    } else {
        painter.fillRect(rect(), QColor("#CCCCCC"));
    }

    QWidget::paintEvent(event);
}

void MainWidget::resizeEvent(QResizeEvent* event)
{
    int windowWidth = width();
    int windowHeight = height();

    // Размеры и позиция menuWidget
    int menuWidth = windowWidth * 600 / 1440;
    int menuHeight = windowHeight * 400 / 1024;
    int offsetX = (windowWidth - menuWidth) / 2;
    int offsetY = windowHeight * 300 / 1024;
    menuWidget->setGeometry(offsetX, offsetY, menuWidth, menuHeight);
    menuWidget->setStyleSheet(QString("background-color: #F0E68C;"));

    // Размеры и позиция windowTitleLabel
    int windowTitleWidth = windowWidth * 800 / 1440;
    int windowTitleHeight = windowHeight * 130 / 1024;
    int titleOffsetX = (windowWidth - windowTitleWidth) / 2;
    int titleOffsetY = windowHeight * 60 / 1024;
    windowTitleLabel->setGeometry(titleOffsetX, titleOffsetY, windowTitleWidth, windowTitleHeight);

    // Расчет начального размера шрифта
    int fontSize = windowTitleHeight / 2; // Исходный размер шрифта — половина высоты
    QFont font = windowTitleLabel->font();
    font.setPointSize(fontSize);

    // Проверка текста на выход за границы
    QFontMetrics metrics(font);
    int textWidth = metrics.horizontalAdvance(windowTitleLabel->text());

    // Если текст шире 90% ширины лейбла, уменьшаем шрифт
    if (textWidth > windowTitleWidth * 0.9) {
        font.setPointSize(windowTitleWidth * 0.9 / textWidth * fontSize); // Пропорциональное уменьшение шрифта
    }

    // Установка финального шрифта
    windowTitleLabel->setFont(font);

    QWidget::resizeEvent(event);
}

void MainWidget::processData(QByteArray& data) {}
