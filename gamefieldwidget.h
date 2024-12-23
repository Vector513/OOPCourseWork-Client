#ifndef GAMEFIELDWIDGET_H
#define GAMEFIELDWIDGET_H

#include "MessageHandlerWidget.h"
#include "GoldBoxWidget.h"

#include <QLabel>
#include <QPixmap>

class GameFieldWidget : public MessageHandlerWidget
{
    Q_OBJECT

public:
    explicit GameFieldWidget(MessageHandler* messageHandler, QWidget *parent = nullptr);

    void resetState() override;
    void start() override;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QVector<GoldBoxWidget*> goldBoxWidgets;

    void resizeEvent(QResizeEvent* event) override;
    void processData(QByteArray& data) override;
};

#endif // MAINWIDGET_H
