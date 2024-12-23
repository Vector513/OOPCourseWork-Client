#ifndef FINDOPPONENTMENUWIDGET_H
#define FINDOPPONENTMENUWIDGET_H

#include "MessageHandlerWidget.h"
#include "MessageHandler.h"

#include <QPushButton>
#include <QLabel>

class FindOpponentMenuWidget : public MessageHandlerWidget
{
    Q_OBJECT

public:
    explicit FindOpponentMenuWidget(MessageHandler* messageHandler, QWidget *parent = nullptr);

    void resetState() override;
    void start() override;

protected:
    void paintEvent(QPaintEvent* event) override;

signals:
    void disconnected();

private slots:
    void onCancelSearchClicked();
    void onTimeout();

private:
    QPushButton* cancelSearchButton;
    QLabel* timePassedLabel;
    QTimer* timer;
    int timeElapsed;

    void resizeEvent(QResizeEvent* event) override;
    void processData(QByteArray& data) override;
};

#endif // MENUWIDGET_H
