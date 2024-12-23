#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QPushButton>
#include "MessageHandlerWidget.h"
#include "MessageHandler.h"

class MenuWidget : public MessageHandlerWidget
{
    Q_OBJECT

public:
    explicit MenuWidget(MessageHandler* messageHandler, QWidget *parent = nullptr);

    void resetState() override;
    void start() override;

protected:
    void paintEvent(QPaintEvent* event) override;

signals:
    void exited();

private slots:
    void onFindOpponentButtonClicked();
    void onExitButtonClicked();

private:
    QPushButton* findOpponentButton;  // Кнопка для поиска противника
    QPushButton* exitButton;          // Кнопка для выхода

    void resizeEvent(QResizeEvent* event) override;
    void processData(QByteArray& data) override;
};

#endif // MENUWIDGET_H
