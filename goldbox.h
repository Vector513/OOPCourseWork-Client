#ifndef GOLDBOX_H
#define GOLDBOX_H

#include <QPushButton>
#include <QIcon>

class GoldBox : public QPushButton {
    Q_OBJECT

public:
    explicit GoldBox(int index, QWidget *parent = nullptr);

    void openBox(int goldAmount);
    void resetBox();
    bool isOpen() const;
    int getGoldAmount() const;
    int getIndex() const;

signals:
    void goldBoxClicked(int index);

private slots:
    void handleClick();

private:
    int index;
    int goldAmount;
    bool open;
    QIcon closedIcon;
    QIcon openedIcon;

    void updateIcon();
};

#endif // GOLDBOX_H
