#include "FindOpponentWidget.h"
#include <QPainter>
#include <QFontMetrics>
#include <QDebug>

FindOpponentWidget::FindOpponentWidget(MessageHandler* messageHandler, QWidget* parent)
    : MessageHandlerWidget(messageHandler, parent),
    menuWidget(new FindOpponentMenuWidget(messageHandler, this)),
    backgroundPixmap(new QPixmap(":/FindOpponentWidgetBackground.jpg")),
    windowTitleLabel(new QLabel("Поиск соперника", this)),
    onlinePlayersLabel(new QLabel(this)),
    onlinePlayers(0)
{
    messageHandler->addWidget("FindOpponentWidget", this);

    windowTitleLabel->setAlignment(Qt::AlignCenter);
    windowTitleLabel->setStyleSheet(
        "background-color: #7AE176; "
        "border-radius: 15px; "
        "border: 3px solid #5A8D3C;"
        );
    onlinePlayersLabel->setAlignment(Qt::AlignCenter);
    onlinePlayersLabel->setStyleSheet("background-color: #F6ED66; font-style: italic;");

    connect(menuWidget, &FindOpponentMenuWidget::disconnected, this, &FindOpponentWidget::disconnected);
}

void FindOpponentWidget::resetState()
{
    menuWidget->resetState();
    onlinePlayers = 0;
    onlinePlayersLabel->setText("Игроков онлайн: 0");
}

void FindOpponentWidget::start()
{
    menuWidget->start();
    onlinePlayersLabel->setText("Подключение к серверу...");
}

void FindOpponentWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    if (backgroundPixmap && !backgroundPixmap->isNull()) {
        painter.drawPixmap(0, 0, width(), height(), *backgroundPixmap);
    } else {
        painter.fillRect(rect(), QColor("#CE9744"));
    }

    QWidget::paintEvent(event);
}

void FindOpponentWidget::resizeEvent(QResizeEvent* event)
{
    int windowWidth = width();
    int windowHeight = height();

    int menuWidth = windowWidth * 600 / 1440;
    int menuHeight = windowHeight * 400 / 1024;
    int menuOffsetX = (windowWidth - menuWidth) / 2;
    int menuOffsetY = windowHeight * 300 / 1024;
    menuWidget->setGeometry(menuOffsetX, menuOffsetY, menuWidth, menuHeight);

    int titleWidth = windowWidth * 800 / 1440;
    int titleHeight = windowHeight * 130 / 1024;
    int titleOffsetX = (windowWidth - titleWidth) / 2;
    int titleOffsetY = windowHeight * 60 / 1024;
    windowTitleLabel->setGeometry(titleOffsetX, titleOffsetY, titleWidth, titleHeight);

    int fontSize = titleHeight / 2;
    QFont titleFont = windowTitleLabel->font();
    titleFont.setPointSize(fontSize);

    QFontMetrics metrics(titleFont);
    int textWidth = metrics.horizontalAdvance(windowTitleLabel->text());

    if (textWidth > titleWidth * 0.9) {
        titleFont.setPointSize(titleWidth * 0.9 / textWidth * fontSize);
    }
    windowTitleLabel->setFont(titleFont);

    int onlineLabelWidth = windowWidth * 3 / 14;
    int onlineLabelHeight = windowHeight / 10;
    int onlineLabelOffsetX = windowWidth * 20 / 1440;
    int onlineLabelOffsetY = windowHeight - windowHeight * 20 / 1024 - onlineLabelHeight;

    onlinePlayersLabel->setGeometry(onlineLabelOffsetX, onlineLabelOffsetY, onlineLabelWidth, onlineLabelHeight);

    int fontSizeOnline = onlineLabelHeight / 2;
    QFont onlineFont = onlinePlayersLabel->font();
    onlineFont.setPointSize(fontSizeOnline);

    QFontMetrics metricsOnline(onlineFont);
    int textWidthOnline = metricsOnline.horizontalAdvance(onlinePlayersLabel->text());

    if (textWidthOnline > onlineLabelWidth * 0.9) {
        onlineFont.setPointSize(onlineLabelWidth * 0.9 / textWidthOnline * fontSizeOnline);
    }

    onlinePlayersLabel->setFont(onlineFont);

    QWidget::resizeEvent(event);
}


void FindOpponentWidget::processData(QByteArray& data)
{
    QString message(data);
    QStringList parts = message.split(' ');

    if (parts.size() > 1 && parts[0] == "OnlinePlayers") {
        bool ok;
        int count = parts[1].toInt(&ok);
        if (ok) {
            onlinePlayers = count;
            onlinePlayersLabel->setText(QString("Игроков онлайн: %1").arg(onlinePlayers));
        } else {
            qDebug() << "Не удалось преобразовать количество игроков: " << message;
        }
    } else {
        qDebug() << "Неизвестное сообщение: " << message;
    }
}

