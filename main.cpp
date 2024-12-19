#include <QApplication>
#include <QStyleFactory>
#include "Application.h"

int main(int argc, char *argv[]) {
    // Инициализация приложения
    QApplication app(argc, argv);

    // Устанавливаем стиль приложения (если хотите применить стиль по умолчанию, можно пропустить эту строку)
    QApplication::setStyle(QStyleFactory::create("Fusion")); // Это для фьюжн стиля, можно использовать другие

    // Создаем и показываем главное окно
    Application application;
    application.show();

    // Запуск основного цикла приложения
    return app.exec();
}
