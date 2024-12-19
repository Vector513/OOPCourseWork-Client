#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QWidget>
#include <QGridLayout>
#include "GoldBox.h"

class GameField : public QWidget {
    Q_OBJECT

public:
    explicit GameField(QWidget *parent = nullptr);
    void setGoldBox(int index, int value);

signals:
    void goldBoxClicked(int index);  // Сигнал, когда ящик с золотом открыт

private:
    QGridLayout *gridLayout;
    QVector<GoldBox *> goldBoxes;  // Вектор для хранения ящиков с золотом
};

#endif // GAMEFIELD_H
