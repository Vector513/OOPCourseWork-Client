#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "MessageHandlerWidget.h"
#include "MenuWidget.h"

#include <QLabel>
#include <QPixmap>

class MainWidget : public MessageHandlerWidget
{
    Q_OBJECT

public:
    explicit MainWidget(MessageHandler* messageHandler, QWidget *parent = nullptr);

    void resetState() override;
    void start() override;

protected:
    void paintEvent(QPaintEvent* event) override;

signals:
    void exited();

private:
    MenuWidget* menuWidget;
    QLabel* windowTitleLabel;
    QPixmap* backgroundPixmap;

    void resizeEvent(QResizeEvent* event) override;
    void processData(QByteArray& data) override;
};

#endif // MAINWIDGET_H
