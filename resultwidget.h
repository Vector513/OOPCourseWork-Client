#ifndef RESULTWIDGET_H
#define RESULTWIDGET_H

#include "MessageHandlerWidget.h"
#include "GameResultWidget.h"

#include <QLabel>
#include <QPushButton>
#include <QPixmap>

class ResultWidget : public MessageHandlerWidget
{
    Q_OBJECT

public:
    explicit ResultWidget(MessageHandler* messageHandler, QWidget *parent = nullptr);

    void resetState() override;
    void start() override;

protected:
    void paintEvent(QPaintEvent* event) override;

signals:
    void exited();

private slots:
    void onExitClicked();

private:
    GameResultWidget* gameResultWidget;
    QLabel* windowTitleLabel;
    QPushButton* returnToMainMenuButton;
    QPixmap* backgroundPixmap;

    void resizeEvent(QResizeEvent* event) override;
    void processData(QByteArray& data) override;
};

#endif // MAINWIDGET_H
