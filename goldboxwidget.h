#ifndef GOLDBOXWIDGET_H
#define GOLDBOXWIDGET_H

#include <QPushButton>
#include "MessageHandlerWidget.h"
#include "MessageHandler.h"

class GoldBoxWidget : public MessageHandlerWidget
{
    Q_OBJECT

public:
    explicit GoldBoxWidget(MessageHandler* messageHandler, int goldBoxIndex, QWidget *parent = nullptr);

    void resetState() override;
    void start() override;

protected:
    void paintEvent(QPaintEvent* event) override;

private slots:
    void onGoldBoxClicked();

private:
    bool isOpen;
    bool isLooted;
    int index;
    QPushButton* goldBoxButton;
    QImage* goldBoxClosedImage;
    QImage* goldBoxOpenedImage;
    QImage* goldBoxLootedImage;

    void setIsOpen(const bool open);
    void setIsLooted(const bool looted);

    void resizeEvent(QResizeEvent* event) override;
    void processData(QByteArray& data) override;
};

#endif // MENUWIDGET_H
