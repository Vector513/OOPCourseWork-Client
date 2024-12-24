#include "ResultWidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QPainter>
#include <QResizeEvent>

ResultWidget::ResultWidget(MessageHandler* messageHandler, QWidget *parent)
    : MessageHandlerWidget(messageHandler, parent),
    gameResultWidget(new GameResultWidget(messageHandler, this)),
    windowTitleLabel(new QLabel("Результат игры", this)),
    returnToMainMenuButton(new QPushButton("Выход", this)),
    backgroundPixmap(new QPixmap(":/GameWidgetBackground.jpg"))  // Замените на путь к вашему фону
{
    messageHandler->addWidget("ResultWidget", this);
    // Настройка лейбла заголовка
    windowTitleLabel->setAlignment(Qt::AlignCenter);
    windowTitleLabel->setStyleSheet(
        "background-color: #7AE176; "
        "border-radius: 15px; "  // Закругленные углы
        "border: 3px solid #5A8D3C;"  // Рамка
        );

    // Настройка кнопки для возврата в главное меню
    returnToMainMenuButton->setStyleSheet("background-color: #E38B19; font-size: 18px; color: black;");
    connect(returnToMainMenuButton, &QPushButton::clicked, this, &ResultWidget::exited);
}

void ResultWidget::resetState()
{
    gameResultWidget->resetState();
}

void ResultWidget::start()
{
    gameResultWidget->start();
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
    int windowWidth = width();
    int windowHeight = height();

    int returnButtonWidth = windowWidth * 250 / 1440;
    int returnButtonHeight = windowHeight * 100 / 1024;
    int returnButtonOffsetX = windowWidth * 30 / 1440;
    int returnButtonOffsetY = windowHeight * 85 / 1024;

    returnToMainMenuButton->setGeometry(returnButtonOffsetX, returnButtonOffsetY, returnButtonWidth, returnButtonHeight);

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

    int gameResultWidth = windowWidth * 600 / 1440;
    int gameResultHeight = windowHeight * 400 / 1024;
    int gameResultOffsetX = (windowWidth - gameResultWidth) / 2;
    int gameResultOffsetY = windowHeight * 300 / 1024;
    gameResultWidget->setGeometry(gameResultOffsetX, gameResultOffsetY, gameResultWidth, gameResultHeight);

    QWidget::resizeEvent(event);
}

void ResultWidget::processData(QByteArray& data)
{

}
