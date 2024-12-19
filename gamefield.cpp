#include "GameField.h"
#include <QDebug>
#include <sstream>

GameField::GameField(TcpClient* otherTcpClient, QWidget *parent)
    : QWidget(parent), tcpClient(otherTcpClient) {
    connect(tcpClient, &TcpClient::messageReceived, this, &GameField::onMessageReceived);

    gridLayout = new QGridLayout(this);
    setupGoldBoxes();
    setLayout(gridLayout);
}

void GameField::setupGoldBoxes() {
    goldBoxes.resize(15);

    int row = 0, col = 0;
    for (int i = 0; i < 15; ++i) {
        GoldBox *box = new GoldBox(i, this);
        goldBoxes[i] = box;

        gridLayout->addWidget(box, row, col);

        connect(box, &GoldBox::goldBoxClicked, this, &GameField::onGoldBoxClicked);

        col++;
        if (col > 4) {
            col = 0;
            row++;
        }
    }
}

void GameField::setGoldBoxValue(int index, int value) {
    if (index >= 0 && index < goldBoxes.size()) {
        goldBoxes[index]->openBox(value);
    } else {
        qDebug() << "Индекс вне диапазона: " << index;
    }
}

void GameField::resetField() {
    for (GoldBox *box : goldBoxes) {
        box->resetBox();
    }
}

void GameField::onGoldBoxClicked(int index) {
    qDebug() << "Сундук с индексом " << index << " был нажат.";
    tcpClient->sendData(QString("opened %1").arg(index));
}

void GameField::onMessageReceived(const QString& message) {
    std::istringstream stream(message.toStdString());
    std::string command;
    int index, goldAmount;

    stream >> command;

    if (command == "opened") {
        stream >> index >> goldAmount;
        setGoldBoxValue(index, goldAmount);
    } else if (command == "reset") {
        resetField();
    }
}
