#ifndef GOLDBOX_H
#define GOLDBOX_H

#include <QWidget>
#include <QPushButton>

class GoldBox : public QWidget {
    Q_OBJECT

public:
    explicit GoldBox(QWidget *parent = nullptr);

signals:
    void goldBoxClicked(int index);  // Сигнал, когда ящик с золотом открыт

private:
    QPushButton *button;  // Кнопка внутри ящика с золотом
    int index;            // Индекс ящика
};

#endif // GOLDBOX_H
