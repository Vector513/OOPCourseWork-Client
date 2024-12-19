#include "GoldBox.h"
#include <QPushButton>
#include <QVBoxLayout>

GoldBox::GoldBox(QWidget *parent) : QWidget(parent), index(-1) {
    button = new QPushButton("Ящик с золотом", this);
    button->setStyleSheet("width: 60px; height: 60px; font-size: 14px;");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(button);
    setLayout(layout);

    connect(button, &QPushButton::clicked, this, [this]() {
        emit goldBoxClicked(index);  // Генерируем сигнал, когда ящик с золотом открыт
    });
}
