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

    timePassedLabel = new QLabel("Времени прошло: 0с", this);
    timePassedLabel->setStyleSheet("background-color: #63A4E5;");
    timePassedLabel->setAlignment(Qt::AlignCenter);

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
    timer->start(1000);
    cancelSearchButton->setEnabled(true);
}

void FindOpponentMenuWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int cornerRadius = std::min(width(), height()) / 16;
    QPainterPath path;
    path.addRoundedRect(rect(), cornerRadius, cornerRadius);

    painter.setBrush(QColor(191, 150, 88, 100));
    painter.drawRect(this->rect());

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

    int labelWidth = windowWidth * 2 / 3;
    int labelHeight = windowHeight * 15 / 40;
    int labelX = (windowWidth - labelWidth) / 2;
    int labelY = windowHeight * 50 / 400;
    timePassedLabel->setGeometry(labelX, labelY, labelWidth, labelHeight);

    int buttonWidth = windowWidth / 2;
    int buttonHeight = windowHeight / 4;
    int buttonX = (windowWidth - buttonWidth) / 2;
    int buttonY = windowHeight - (windowHeight / 8) - buttonHeight;
    cancelSearchButton->setGeometry(buttonX, buttonY, buttonWidth, buttonHeight);

    int fontSize = buttonHeight / 2;
    QFont font = cancelSearchButton->font();
    font.setPointSize(fontSize);

    QFontMetrics metrics(font);

    int buttonTextWidth = metrics.horizontalAdvance(cancelSearchButton->text());
    if (buttonTextWidth > buttonWidth * 0.9) {
        font.setPointSize(buttonWidth * 0.9 / buttonTextWidth * fontSize);
    }

    int labelTextWidth = metrics.horizontalAdvance(timePassedLabel->text());
    if (labelTextWidth > labelWidth * 0.9) {
        font.setPointSize(labelWidth * 0.9 / labelTextWidth * fontSize);
    }

    cancelSearchButton->setFont(font);
    timePassedLabel->setFont(font);

    QWidget::resizeEvent(event);
}


void FindOpponentMenuWidget::processData(QByteArray& data)
{
    QString message = QString::fromUtf8(data);


}
