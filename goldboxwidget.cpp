#include "GoldBoxWidget.h"
#include <QPainter>
#include <QResizeEvent>

GoldBoxWidget::GoldBoxWidget(MessageHandler* messageHandler, int goldBoxIndex, QWidget* parent)
    : MessageHandlerWidget(messageHandler, parent),
    isOpen(false),
    isLooted(false),
    index(goldBoxIndex), // Инициализация index
    goldBoxButton(new QPushButton(this)),
    goldBoxClosedImage(new QImage(":/GoldBoxClosed.jpg")), // Изображение закрытого сундука
    goldBoxOpenedImage(new QImage(":/GoldBoxOpened.jpg")), // Изображение открытого сундука
    goldBoxLootedImage(new QImage(":/GoldBoxLooted.jpg")) // Изображение залутанного сундука
{
    messageHandler->addWidget("GoldBox" + QString::number(index), this);

    if (goldBoxClosedImage && !goldBoxClosedImage->isNull()) {
        for (int y = 0; y < goldBoxClosedImage->height(); ++y) {
            for (int x = 0; x < goldBoxClosedImage->width(); ++x) {
                if (goldBoxClosedImage->pixelColor(x, y) == Qt::white) {
                    goldBoxClosedImage->setPixelColor(x, y, Qt::transparent);
                }
            }
        }
    }

    goldBoxButton->setFlat(true);
    goldBoxButton->setGeometry(this->rect());
    connect(goldBoxButton, &QPushButton::clicked, this, &GoldBoxWidget::onGoldBoxClicked);
}

void GoldBoxWidget::resetState()
{
    isOpen = false;
    isLooted = false;
    update();
}

void GoldBoxWidget::start()
{
    resetState();
}

void GoldBoxWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    QImage* currentImage = nullptr;

    // Выбираем изображение в зависимости от состояния
    if (isLooted) {
        currentImage = goldBoxLootedImage; // Изображение для залутанного сундука
    } else if (isOpen) {
        currentImage = goldBoxOpenedImage; // Изображение для открытого сундука
    } else {
        currentImage = goldBoxClosedImage; // Изображение для закрытого сундука
    }

    if (currentImage && !currentImage->isNull()) {
        // Рисуем спрайт, центрируя его
        QRect targetRect = this->rect();
        QRect sourceRect(0, 0, currentImage->width(), currentImage->height());
        painter.drawImage(targetRect, *currentImage, sourceRect);
    }

    QWidget::paintEvent(event);
}

void GoldBoxWidget::onGoldBoxClicked()
{
    if (!isOpen && !isLooted) {
        messageHandler->sendData("GameSession GoldBoxOpened " + QByteArray::number(index) + " Opened");
    }
}

void GoldBoxWidget::setIsOpen(const bool open)
{
    isOpen = open;
    update();
}

void GoldBoxWidget::setIsLooted(const bool looted)
{
    isLooted = looted;
    update();
}

void GoldBoxWidget::resizeEvent(QResizeEvent* event)
{
    if (goldBoxButton) {
        goldBoxButton->setGeometry(this->rect());
    }
    QWidget::resizeEvent(event);
}

void GoldBoxWidget::processData(QByteArray& data)
{
    if (data.startsWith("Opened")) {
        setIsOpen(true);
    }
    else if (data.startsWith("Looted")) {
        setIsLooted(true);
    }
}
