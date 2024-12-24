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

    QList<QLabel*> labels = {widgetTitle, coinsLabel, movesLeftForYouLabel,
                              movesLeftForOpponentLabel, isOpponentLootedLabel,
                              canMakeMoveLabel};

    for (auto* label : labels) {
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("font-size: 14px; color: white; background-color: rgba(0, 0, 0, 0.6); border: 1px solid white; padding: 4px;");
    }

    widgetTitle->setStyleSheet("font-size: 16px; font-weight: bold; color: yellow; background-color: rgba(0, 0, 0, 0.8); border: 1px solid yellow; padding: 6px;");
}

void GameInfoWidget::resetState()
{
    // Сбрасываем значения лейблов
    coinsLabel->setText("В ящике: ? монет");
    movesLeftForYouLabel->setText("Ходов у вас осталось: ?");
    movesLeftForOpponentLabel->setText("Ходов у соперника осталось: ?");
    isOpponentLootedLabel->setText("Соперник не брал золото");
    canMakeMoveLabel->setText("Ждите");
}

void GameInfoWidget::start()
{
    // Начальное состояние игры может быть установлено здесь
}

void GameInfoWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    // Полупрозрачный фон
    QColor backgroundColor = Qt::darkBlue;
    backgroundColor.setAlpha(200);
    painter.fillRect(this->rect(), backgroundColor);

    QWidget::paintEvent(event);
}

void GameInfoWidget::resizeEvent(QResizeEvent* event)
{
    // Обновляем геометрию элементов при изменении размера
    int width = this->width();
    int height = this->height();

    int labelHeight = height / 6;

    widgetTitle->setGeometry(0, 0, width, labelHeight);
    coinsLabel->setGeometry(0, labelHeight, width, labelHeight);
    movesLeftForYouLabel->setGeometry(0, 2 * labelHeight, width, labelHeight);
    movesLeftForOpponentLabel->setGeometry(0, 3 * labelHeight, width, labelHeight);
    isOpponentLootedLabel->setGeometry(0, 4 * labelHeight, width, labelHeight);
    canMakeMoveLabel->setGeometry(0, 5 * labelHeight, width, labelHeight);

    QWidget::resizeEvent(event);
}

void GameInfoWidget::processData(QByteArray& data)
{
    // Разделяем данные по пробелам
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
    } else if (command == "YourTurn") {
        canMakeMoveLabel->setText("Ходите");
    } else if (command == "Wait") {
        canMakeMoveLabel->setText("Ждите");
    } else if (command == "MovesLeftForYou") {
        movesLeftForYouLabel->setText("Ходов у вас осталось: " + value);
    } else if (command == "MovesLeftForOpponent") {
        movesLeftForYouLabel->setText("Ходов у вас осталось: " + value);
    }
}
