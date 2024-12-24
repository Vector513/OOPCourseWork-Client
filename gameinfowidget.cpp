#include "GameInfoWidget.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QResizeEvent>

GameInfoWidget::GameInfoWidget(MessageHandler* messageHandler, QWidget* parent)
    : MessageHandlerWidget(messageHandler, parent),
    widgetTitle(new QLabel("Инфо", this)),
    coinsLabel(new QLabel("В ящике: ? монет", this)),
    movesLeftForYouLabel(new QLabel("Ходов у вас осталось: ?", this)),
    movesLeftForOpponentLabel(new QLabel("Ходов у соперника осталось: ?", this)),
    isOpponentLootedLabel(new QLabel("Соперник не брал золото", this)),
    canMakeMoveLabel(new QLabel("Ждите", this))
{
    messageHandler->addWidget("GameInfoWidget", this);

    widgetTitle->setAlignment(Qt::AlignCenter);
    isOpponentLootedLabel->setAlignment(Qt::AlignCenter);
    canMakeMoveLabel->setAlignment(Qt::AlignCenter);

    isOpponentLootedLabel->setStyleSheet("background-color: #76ED6E;");
    canMakeMoveLabel->setStyleSheet("background-color: #EB4848;");
}

void GameInfoWidget::resetState()
{
    coinsLabel->setText("В ящике: ? монет");
    movesLeftForYouLabel->setText("Ходов у вас осталось: ?");
    movesLeftForOpponentLabel->setText("Ходов у соперника осталось: ?");
    isOpponentLootedLabel->setText("Соперник не брал золото");
    isOpponentLootedLabel->setStyleSheet("background-color: #76ED6E;");
    canMakeMoveLabel->setText("Ждите");
    canMakeMoveLabel->setStyleSheet("background-color: #EB4848");
}

void GameInfoWidget::start()
{
    return;
}

void GameInfoWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    painter.setBrush(QColor(215, 200, 13, 50));
    painter.drawRect(this->rect());

    QWidget::paintEvent(event);
}

void setFontSizeToFitLabel(QLabel* label, int labelWidth, int labelHeight) {
    int fontSize = labelHeight / 2;
    QFont font = label->font();
    font.setPointSize(fontSize);

    QFontMetrics metrics(font);
    int textWidth = metrics.horizontalAdvance(label->text());

    if (textWidth > labelWidth * 0.9) {
        font.setPointSize(labelWidth * 0.9 / textWidth * fontSize);
    }

    label->setFont(font);
}

void GameInfoWidget::resizeEvent(QResizeEvent* event)
{
    int windowWidth = width();
    int windowHeight = height();

    int widgetTitleWidth = windowWidth * 360 / 400;
    int widgetTitleHeight = windowHeight * 85 / 600;
    int widgetTitleOffsetX = windowWidth * 20 / 400;
    int widgetTitleOffsetY = windowHeight * 20 / 600;

    widgetTitle->setGeometry(widgetTitleOffsetX, widgetTitleOffsetY, widgetTitleWidth, widgetTitleHeight);

    int coinsLabelWidth = windowWidth * 360 / 400;
    int coinsLabelHeight = windowHeight * 85 / 600;
    int coinsLabelOffsetX = windowWidth * 20 / 400;
    int coinsLabelOffsetY = windowHeight * 75 / 600;

    coinsLabel->setGeometry(coinsLabelOffsetX, coinsLabelOffsetY, coinsLabelWidth, coinsLabelHeight);

    int movesLeftForYouLabelWidth = windowWidth * 360 / 400;
    int movesLeftForYouLabelHeight = windowHeight * 85 / 600;
    int movesLeftForYouLabelOffsetX = windowWidth * 20 / 400;
    int movesLeftForYouLabelOffsetY = windowHeight * 130 / 600;

    movesLeftForYouLabel->setGeometry(movesLeftForYouLabelOffsetX, movesLeftForYouLabelOffsetY, movesLeftForYouLabelWidth, movesLeftForYouLabelHeight);

    int movesLeftForOpponentLabelWidth = windowWidth * 360 / 400;
    int movesLeftForOpponentLabelHeight = windowHeight * 85 / 600;
    int movesLeftForOpponentLabelOffsetX = windowWidth * 20 / 400;
    int movesLeftForOpponentLabelOffsetY = windowHeight * 195 / 600;

    movesLeftForOpponentLabel->setGeometry(movesLeftForOpponentLabelOffsetX, movesLeftForOpponentLabelOffsetY, movesLeftForOpponentLabelWidth, movesLeftForOpponentLabelHeight);

    int isOpponentLootedLabelWidth = windowWidth * 340 / 400;
    int isOpponentLootedLabelHeight = windowHeight * 140 / 600;
    int isOpponentLootedLabelOffsetX = windowWidth * 30 / 400;
    int isOpponentLootedLabelOffsetY = windowHeight * 255 / 600;

    isOpponentLootedLabel->setGeometry(isOpponentLootedLabelOffsetX, isOpponentLootedLabelOffsetY, isOpponentLootedLabelWidth, isOpponentLootedLabelHeight);

    int canMakeMoveLabelWidth = windowWidth * 340 / 400;
    int canMakeMoveLabelHeight = windowHeight * 140 / 600;
    int canMakeMoveLabelOffsetX = windowWidth * 30 / 400;
    int canMakeMoveLabelOffsetY = windowHeight * 420 / 600;

    canMakeMoveLabel->setGeometry(canMakeMoveLabelOffsetX, canMakeMoveLabelOffsetY, canMakeMoveLabelWidth, canMakeMoveLabelHeight);

    setFontSizeToFitLabel(widgetTitle, widgetTitleWidth, widgetTitleHeight);
    setFontSizeToFitLabel(coinsLabel, coinsLabelWidth, coinsLabelHeight);
    setFontSizeToFitLabel(movesLeftForYouLabel, movesLeftForYouLabelWidth, movesLeftForYouLabelHeight);
    setFontSizeToFitLabel(movesLeftForOpponentLabel, movesLeftForOpponentLabelWidth, movesLeftForOpponentLabelHeight);
    setFontSizeToFitLabel(canMakeMoveLabel, canMakeMoveLabelWidth, canMakeMoveLabelHeight);
    setFontSizeToFitLabel(isOpponentLootedLabel, isOpponentLootedLabelWidth, isOpponentLootedLabelHeight);

    QWidget::resizeEvent(event);
}

void GameInfoWidget::processData(QByteArray& data)
{
    QList<QByteArray> parts = data.split(' ');

    if (parts.isEmpty()) return;

    QString command = QString::fromUtf8(parts[0]);
    QString value = parts.size() > 1 ? QString::fromUtf8(parts[1]) : QString();

    if (command == "Coins") {
        if (value.isEmpty()) {
            coinsLabel->setText("В ящике: ?");
        } else {
            coinsLabel->setText("В ящике: " + value + " монет");
        }
    } else if (command == "OpponentLooted") {
        isOpponentLootedLabel->setText("Соперник забрал золото!");
        isOpponentLootedLabel->setStyleSheet("background-color: #EB4848;");
    } else if (command == "YourTurn") {
        canMakeMoveLabel->setText("Ходите");
        canMakeMoveLabel->setStyleSheet("background-color: #76ED6E");
    } else if (command == "Wait") {
        canMakeMoveLabel->setText("Ждите");
        canMakeMoveLabel->setStyleSheet("background-color: #EB4848");
    } else if (command == "MovesLeftForYou") {
        movesLeftForYouLabel->setText("Ходов у вас осталось: " + value);
    } else if (command == "MovesLeftForOpponent") {
        movesLeftForOpponentLabel->setText("Ходов у соперника осталось: " + value);
    }
}
