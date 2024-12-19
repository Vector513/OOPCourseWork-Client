#include "GoldBox.h"

GoldBox::GoldBox(int index, QWidget *parent)
    : QPushButton(parent), index(index), goldAmount(0), open(false),
    closedIcon(":/images/images/goldBoxClosed.jpg"), openedIcon(":/images/images/goldBoxOpened.jpg") {
    setIcon(closedIcon);
    setIconSize(QSize(64, 64));
    setFlat(true);
    setStyleSheet("border: none;");

    connect(this, &QPushButton::clicked, this, &GoldBox::handleClick);
}

void GoldBox::handleClick() {
    emit goldBoxClicked(index);
}

void GoldBox::openBox(int goldAmount) {
    if (!open) {
        this->goldAmount = goldAmount;
        open = true;
        updateIcon();
    }
}

void GoldBox::resetBox() {
    goldAmount = 0;
    open = false;
    updateIcon();
}

bool GoldBox::isOpen() const {
    return open;
}

int GoldBox::getGoldAmount() const {
    return goldAmount;
}

int GoldBox::getIndex() const {
    return index;
}

void GoldBox::updateIcon() {
    setIcon(open ? openedIcon : closedIcon);
}
