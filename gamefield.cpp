#include "GameField.h"
#include <QGridLayout>

GameField::GameField(QWidget *parent) : QWidget(parent) {
    gridLayout = new QGridLayout(this);
    goldBoxes.resize(15);  // Резервируем место для 15 ящиков с золотом

    int row = 0, col = 0;
    for (int i = 0; i < 15; ++i) {
        goldBoxes[i] = new GoldBox(this);
        goldBoxes[i]->setObjectName(QString::number(i));  // Присваиваем уникальное имя
        gridLayout->addWidget(goldBoxes[i], row, col);
        connect(goldBoxes[i], &GoldBox::goldBoxClicked, this, &GameField::goldBoxClicked);

        col++;
        if (col > 4) {  // Переход к новой строке после 5 ящиков
            col = 0;
            row++;
        }
    }

    setLayout(gridLayout);
}

void GameField::setGoldBox(int index, int value) {
    // Здесь можно добавить логику для изменения состояния ящика (например, открыть его)
}
