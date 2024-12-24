#include "GameWidget.h"
#include "GameFieldWidget.h"
#include "GameInfoWidget.h"

#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <QHBoxLayout>

GameWidget::GameWidget(MessageHandler* messageHandler, QWidget* parent)
    : MessageHandlerWidget(messageHandler, parent),
    gameFieldWidget(new GameFieldWidget(messageHandler, this)),
    gameInfoWidget(new GameInfoWidget(messageHandler, this)),
    backgroundPixmap(new QPixmap(":/GameWidgetBackground.jpg")),
    windowTitleLabel(new QLabel("Окно игры", this)),
    returnToMainMenuButton(new QPushButton("Выйти", this)),
    timerLabel(new QLabel("00:00", this)),
    finishButton(new QPushButton("Взять и закончить", this)),
    continueButton(new QPushButton("Продолжить", this)),
    timer(new QTimer(this)),
    elapsedTime(0)
{
    messageHandler->addWidget("GameWidget", this);
    setAutoFillBackground(true);

    windowTitleLabel->setAlignment(Qt::AlignCenter);
    windowTitleLabel->setStyleSheet(
        "background-color: #7AE176; "
        "border-radius: 15px; "
        "border: 3px solid #5A8D3C;"
        );

    timerLabel->setAlignment(Qt::AlignCenter);
    timerLabel->setStyleSheet("font-size: 14px; color: white;");

    connect(timer, &QTimer::timeout, this, [this]() {
        elapsedTime++;
        int minutes = elapsedTime / 60;
        int seconds = elapsedTime % 60;
        timerLabel->setText(QString::asprintf("%02d:%02d", minutes, seconds));
    });

    returnToMainMenuButton->setStyleSheet("background-color: #E38B19; color: black;");
    timerLabel->setStyleSheet("background-color: #E38B19; color: black;");
    finishButton->setStyleSheet("background-color: #E64646; color: white;");
    continueButton->setStyleSheet("background-color: #6AD4E9; color: white;");

    connect(returnToMainMenuButton, &QPushButton::clicked, this, &GameWidget::onExitClicked);
    connect(finishButton, &QPushButton::clicked, this, &GameWidget::onFinishClicked);
    connect(continueButton, &QPushButton::clicked, this, &GameWidget::onContinueClicked);

    timer->start(1000);
}

void GameWidget::resetState()
{
    gameFieldWidget->resetState();
    gameInfoWidget->resetState();
    elapsedTime = 0;
    timerLabel->setText("00:00");
}

void GameWidget::start()
{
    elapsedTime = 0;
    timerLabel->setText("00:00");
    gameFieldWidget->start();
    gameInfoWidget->start();
}

void GameWidget::onExitClicked()
{
    messageHandler->disconnectFromServer();
    emit disconnected();
}

void GameWidget::onFinishClicked()
{
    messageHandler->sendData("GameSession Finish");
}

void GameWidget::onContinueClicked()
{
    messageHandler->sendData("GameSession Continue");
}

void GameWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    if (backgroundPixmap && !backgroundPixmap->isNull()) {
        painter.drawPixmap(0, 0, width(), height(), *backgroundPixmap);
    } else {
        painter.fillRect(rect(), QColor("#CE9744"));
    }

    QWidget::paintEvent(event);
}

void GameWidget::resizeEvent(QResizeEvent* event)
{
    int windowWidth = width();
    int windowHeight = height();

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

    int returnButtonWidth = windowWidth * 250 / 1440;
    int returnButtonHeight = windowHeight * 100 / 1024;
    int returnButtonOffsetX = windowWidth * 30 / 1440;
    int returnButtonOffsetY = windowHeight * 85 / 1024;

    returnToMainMenuButton->setGeometry(returnButtonOffsetX, returnButtonOffsetY, returnButtonWidth, returnButtonHeight);

    fontSize = returnButtonHeight / 2;
    font = returnToMainMenuButton->font();
    font.setPointSize(fontSize);

    metrics = QFontMetrics(font);
    textWidth = metrics.horizontalAdvance(returnToMainMenuButton->text());

    if (textWidth > returnButtonWidth * 0.9) {
        font.setPointSize(returnButtonWidth * 0.9 / textWidth * fontSize);
    }

    returnToMainMenuButton->setFont(font);

    int timerLabelWidth = windowWidth * 250 / 1440;
    int timerLabelHeight = windowHeight * 100 / 1024;
    int timerLabelOffsetX = windowWidth * 1155 / 1440;
    int timerLabelOffsetY = windowHeight * 85 / 1024;

    timerLabel->setGeometry(timerLabelOffsetX, timerLabelOffsetY, timerLabelWidth, timerLabelHeight);

    int gameFieldWidth = windowWidth * 900 / 1440;
    int gameFieldHeight = windowHeight * 600 / 1024;
    int gameFieldOffsetX = windowWidth * 35 / 1440;
    int gameFieldOffsetY = windowHeight * 250 / 1024;

    gameFieldWidget->setGeometry(gameFieldOffsetX, gameFieldOffsetY, gameFieldWidth, gameFieldHeight);

    int gameInfoWidth = windowWidth * 400 / 1440;
    int gameInfoHeight = windowHeight * 600 / 1024;
    int gameInfoOffsetX = windowWidth * 990 / 1440;
    int gameInfoOffsetY = windowHeight * 250 / 1024;

    gameInfoWidget->setGeometry(gameInfoOffsetX, gameInfoOffsetY, gameInfoWidth, gameInfoHeight);

    int finishButtonWidth = windowWidth * 420 / 1440;
    int finishButtonHeight = windowHeight * 75 / 1024;
    int finishButtonOffsetX = windowWidth * 35 / 1440;
    int finishButtonOffsetY = windowHeight * 880 / 1024;

    finishButton->setGeometry(finishButtonOffsetX, finishButtonOffsetY, finishButtonWidth, finishButtonHeight);

    int continueButtonWidth = windowWidth * 420 / 1440;
    int continueButtonHeight = windowHeight * 75 / 1024;
    int continueButtonOffsetX = windowWidth * 515 / 1440;
    int continueButtonOffsetY = windowHeight * 880 / 1024;

    continueButton->setGeometry(continueButtonOffsetX, continueButtonOffsetY, continueButtonWidth, continueButtonHeight);

    QWidget::resizeEvent(event);
}


void GameWidget::processData(QByteArray& data)
{
    return;
}
