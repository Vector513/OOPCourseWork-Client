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
        "border-radius: 15px; "
        "border: 3px solid #5A8D3C;"
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

    int menuWidth = windowWidth * 600 / 1440;
    int menuHeight = windowHeight * 400 / 1024;
    int offsetX = (windowWidth - menuWidth) / 2;
    int offsetY = windowHeight * 300 / 1024;
    menuWidget->setGeometry(offsetX, offsetY, menuWidth, menuHeight);
    menuWidget->setStyleSheet(QString("background-color: #F0E68C;"));

    int windowTitleWidth = windowWidth * 800 / 1440;
    int windowTitleHeight = windowHeight * 130 / 1024;
    int titleOffsetX = (windowWidth - windowTitleWidth) / 2;
    int titleOffsetY = windowHeight * 60 / 1024;
    windowTitleLabel->setGeometry(titleOffsetX, titleOffsetY, windowTitleWidth, windowTitleHeight);

    int fontSize = windowTitleHeight / 2;
    QFont font = windowTitleLabel->font();
    font.setPointSize(fontSize);

    QFontMetrics metrics(font);
    int textWidth = metrics.horizontalAdvance(windowTitleLabel->text());

    if (textWidth > windowTitleWidth * 0.9) {
        font.setPointSize(windowTitleWidth * 0.9 / textWidth * fontSize);
    }

    windowTitleLabel->setFont(font);

    QWidget::resizeEvent(event);
}

void MainWidget::processData(QByteArray& data) {}
