#include "MainWindow.h"
#include <QPixmap>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

MainWindow::MainWindow(TcpClient *otherTcpClient, QWidget *parent)
    : QWidget(parent)
    , tcpClient(otherTcpClient)
{
    setWindowTitle("Главное окно");
    setMinimumSize(400, 300);
    //resize(1280, 720);

    // Основной layout для окна
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Фоновое изображение
    backgroundLabel = new QLabel(this);
    QPixmap backgroundPixmap(":/images/images/background2.jpg");  // Путь к картинке
    backgroundLabel->setPixmap(backgroundPixmap.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    backgroundLabel->setStyleSheet("background-color: transparent;");
    backgroundLabel->resize(this->size());  // Растягиваем картинку на всё окно
    backgroundLabel->setScaledContents(true); // Разрешаем растягивание картинки
    // Создаем layout для backgroundLabel

    QVBoxLayout *backgroundLayout = new QVBoxLayout(backgroundLabel);
    backgroundLabel->setLayout(backgroundLayout);  // Устанавливаем layout для backgroundLabel

    // Создаем экземпляр меню
    menu = new Menu(tcpClient, backgroundLabel);
    menu->setStyleSheet("background-color: transparent;"); // Меню с прозрачным фоном

    // Добавляем меню в layout backgroundLabel
    backgroundLayout->addWidget(menu, 0, Qt::AlignCenter);  // Центрируем меню

    // Добавляем backgroundLabel в основной layout окна
    mainLayout->addWidget(backgroundLabel, 0, Qt::AlignCenter);

    setLayout(mainLayout);

    // Подключаем сигнал от кнопки "Найти соперника" к слоту (например, для переключения на другое окно)
    connect(menu, &Menu::findOpponentClicked, this, &MainWindow::findOpponentClicked);
}
