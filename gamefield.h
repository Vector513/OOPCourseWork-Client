#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "TcpClient.h"
#include "GoldBox.h"

#include <QWidget>
#include <QGridLayout>
#include <QVector>

class GameField : public QWidget {
    Q_OBJECT

public:
    explicit GameField(TcpClient* otherTcpClient, QWidget *parent = nullptr);
    void setGoldBoxValue(int index, int value);
    void resetField();

signals:
    void goldBoxClicked(int index);

private slots:
    void onGoldBoxClicked(int index);
    void onMessageReceived(const QString& message);

private:
    TcpClient* tcpClient;
    QGridLayout *gridLayout;
    QVector<GoldBox *> goldBoxes;

    void setupGoldBoxes();
};

#endif // GAMEFIELD_H
