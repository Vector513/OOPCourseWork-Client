#include "Application.h"
#include "qapplication.h"
#include <QVBoxLayout>

#include <QPainter>

Application::Application(MessageHandler* messageHandler, QWidget *parent)
    : MessageHandlerWidget(messageHandler, parent)  // Вызов конструктора базового класса
{
    resize(800, 450);

    messageHandler->addWidget("Application", this);

    stackedWidget = new QStackedWidget;
    mainWidget = new MainWidget(messageHandler, this);
    findOpponentWidget = new FindOpponentWidget(messageHandler, this);
    gameWidget = new GameWidget(messageHandler, this);
    resultWidget = new ResultWidget(messageHandler, this);

    stackedWidget->addWidget(mainWidget);
    stackedWidget->addWidget(findOpponentWidget);
    stackedWidget->addWidget(gameWidget);
    stackedWidget->addWidget(resultWidget);
    stackedWidget->setCurrentWidget(mainWidget);

    QVBoxLayout* layout = new QVBoxLayout(this); // Компоновка для родителя
    layout->setContentsMargins(0, 0, 0, 0);     // Убираем отступы
    layout->setSpacing(0);                      // Убираем промежутки
    layout->addWidget(stackedWidget);              // Добавляем виджет

    setLayout(layout);

    connect(mainWidget, &MainWidget::exited, this, &Application::onExited);
    connect(findOpponentWidget, &FindOpponentWidget::disconnected, this, &Application::onReturnToMainMenu);
    connect(gameWidget, &GameWidget::disconnected, this, &Application::onReturnToMainMenu);
    connect(resultWidget, &ResultWidget::exited, this, &Application::onReturnToMainMenu);
}

Application::~Application()
{
    delete mainWidget;
}

void Application::resetState() {

}

void Application::start() {

}

void Application::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    painter.fillRect(rect(), QColor("#ffce52"));

    QWidget::paintEvent(event);
}

void Application::onExited()
{
    QApplication::quit();
}

void Application::onReturnToMainMenu()
{
    stackedWidget->setCurrentWidget(mainWidget);
    mainWidget->start();
    findOpponentWidget->resetState();
}

void Application::processData(QByteArray& data)
{
    QString strData = QString::fromUtf8(data);

    qDebug() << "Mne prishlo: " << strData;

    QStringList words = strData.split(" ");

    if (!words.isEmpty() && words.first() == "FindOpponentWidget") {
        findOpponentWidget->start();
        stackedWidget->setCurrentWidget(findOpponentWidget);
        mainWidget->resetState();
    } else if (!words.isEmpty() && words.first() == "OpponentFound") {
        gameWidget->start();
        stackedWidget->setCurrentWidget(gameWidget);
        findOpponentWidget->resetState();
    } else if (!words.isEmpty() && words.first() == "GameOver") {
        qDebug() << "Я здессссссссссссссссссссссссссссссс";
        resultWidget->start();
        stackedWidget->setCurrentWidget(resultWidget);
        gameWidget->resetState();
    }
}

