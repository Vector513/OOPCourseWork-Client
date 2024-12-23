#ifndef APPLICATION_H
#define APPLICATION_H

#include "MessageHandlerWidget.h"
#include "MainWidget.h"
#include "FindOpponentWidget.h"
#include <QStackedWidget>

class Application : public MessageHandlerWidget
{
    Q_OBJECT

public:
    Application(MessageHandler* messaheHandler, QWidget *parent = nullptr);
    ~Application();

    void resetState() override;
    void start() override;

protected:
    void paintEvent(QPaintEvent* event) override;

private slots:
    void onExited();
    void onDisconnected();

private:
    QStackedWidget* stackedWidget;
    MainWidget* mainWidget;
    FindOpponentWidget* findOpponentWidget;

    void processData(QByteArray& data) override;
};
#endif // APPLICATION_H
