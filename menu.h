#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class Menu : public QWidget
{
    Q_OBJECT
public:
    explicit Menu(QWidget *parent = nullptr);

signals:
    void findOpponentClicked(); // Сигнал, который будет испущен при нажатии кнопки "Найти соперника"

private:
    QPushButton *findOpponentButton; // Кнопка "Найти соперника"
};

#endif // MENU_H
