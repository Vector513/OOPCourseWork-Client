#include "GoldBoxWidget.h"
#include <QPainter>
#include <QResizeEvent>

GoldBoxWidget::GoldBoxWidget(MessageHandler* messageHandler, int goldBoxIndex, QWidget* parent)
    : MessageHandlerWidget(messageHandler, parent),
    isOpen(false),
    isLooted(false),
    index(goldBoxIndex),
    goldBoxButton(new QPushButton(this)),
    goldBoxClosedImage(new QImage(":/GoldBoxClosed.jpg")),
    goldBoxOpenedImage(new QImage(":/GoldBoxOpened.jpg")),
    goldBoxLootedImage(new QImage(":/GoldBoxLooted.jpg"))
{
    messageHandler->addWidget("GoldBox" + QString::number(index), this);

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

    if (isLooted) {
        currentImage = goldBoxLootedImage;
    } else if (isOpen) {
        currentImage = goldBoxOpenedImage;
    } else {
        currentImage = goldBoxClosedImage;
    }

    if (currentImage && !currentImage->isNull()) {
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
