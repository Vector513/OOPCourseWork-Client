#include "MenuWidget.h"

#include <QVBoxLayout>
#include <QPalette>
#include <QPainter>
#include <QPainterPath>
#include <QFontMetrics>

MenuWidget::MenuWidget(MessageHandler* messageHandler, QWidget *parent)
    : MessageHandlerWidget(messageHandler, parent)
{
    messageHandler->addWidget("MenuWidget", this);

    setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(206, 151, 68));
    setPalette(palette);

    findOpponentButton = new QPushButton("Найти соперника", this);
    findOpponentButton->setStyleSheet("background-color: #4FB7BD;");

    connect(findOpponentButton, &QPushButton::clicked, this, &MenuWidget::onFindOpponentButtonClicked);

    exitButton = new QPushButton("Выйти", this);
    exitButton->setStyleSheet("background-color: #DB4A4A;");

    connect(exitButton, &QPushButton::clicked, this, &MenuWidget::onExitButtonClicked);
}

void MenuWidget::resetState()
{
    findOpponentButton->setEnabled(false);
    exitButton->setEnabled(false);
}

void MenuWidget::start()
{
    findOpponentButton->setEnabled(true);
    exitButton->setEnabled(true);
}

void MenuWidget::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // Включаем антиалиасинг для сглаживания углов

    // Устанавливаем прозрачность (например, 50% прозрачности)
    painter.setOpacity(0.5);

    // Вычисляем радиус закругления в зависимости от ширины или высоты виджета
    int cornerRadius = std::min(width(), height()) / 16;  // Радиус пропорционален меньшему размеру виджета

    // Создаем путь с закругленными углами
    QPainterPath path;
    path.addRoundedRect(rect(), cornerRadius, cornerRadius);  // Устанавливаем радиус закругления для всех углов

    // Заливаем закругленный прямоугольник цветом с прозрачностью
    painter.fillPath(path, QColor(206, 151, 68));  // Цвет фона

    // Вставьте дополнительную отрисовку элементов, если необходимо (например, кнопки, текст и т.д.)

    QWidget::paintEvent(event);  // Вызов базового paintEvent
}


void MenuWidget::resizeEvent(QResizeEvent* event)
{
    int windowWidth = width();
    int windowHeight = height();

    int buttonWidth = windowWidth / 2;
    int buttonHeight = windowHeight / 4;

    int offsetX = (windowWidth - buttonWidth) / 2;

    int topButtonOffsetY = windowHeight * 85 / 400;
    int bottomButtonOffsetY = windowHeight * 85 / 400;

    findOpponentButton->setGeometry(offsetX, topButtonOffsetY, buttonWidth, buttonHeight);
    exitButton->setGeometry(offsetX, windowHeight - bottomButtonOffsetY - buttonHeight, buttonWidth, buttonHeight);

    int borderRadius = 12 * buttonHeight / 100;
    findOpponentButton->setStyleSheet(QString("background-color: #4FB7BD; border-radius: %1px;").arg(borderRadius));
    exitButton->setStyleSheet(QString("background-color: #DB4A4A; border-radius: %1px;").arg(borderRadius));

    int fontSize = buttonHeight / 2;  // Исходный размер шрифта - половина высоты кнопки
    QFont font = findOpponentButton->font();
    font.setPointSize(fontSize);

    QFontMetrics metrics(font);
    int textWidth = metrics.horizontalAdvance(findOpponentButton->text());

    // Если текст занимает более 90% ширины кнопки, уменьшаем размер шрифта
    if (textWidth > buttonWidth * 0.9) {
        font.setPointSize(buttonWidth * 0.9 / textWidth * fontSize);  // Уменьшаем шрифт пропорционально
    }

    // Применяем одинаковый размер шрифта к обеим кнопкам
    findOpponentButton->setFont(font);
    exitButton->setFont(font);

    QWidget::resizeEvent(event);
}

void MenuWidget::onFindOpponentButtonClicked()
{
    messageHandler->connectToServer("192.168.31.227", 10001);
}

void MenuWidget::onExitButtonClicked()
{
    emit exited();
}

void MenuWidget::processData(QByteArray& data)
{
    return;
}
