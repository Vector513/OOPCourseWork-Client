#ifndef OPPONENTSEARCHWINDOW_H
#define OPPONENTSEARCHWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>

class OpponentSearchWindow : public QWidget {
    Q_OBJECT

public:
    explicit OpponentSearchWindow(QWidget *parent = nullptr);

signals:
    void searchCanceled(); // Сигнал для возврата в меню
    void startTmpGame();

private:
    QLabel *timerLabel;     // Для отображения времени
    QTimer *timer;          // Таймер для отсчета времени
    int elapsedTime;        // Счетчик секунд

    //QPushButton *tmpGameButton;

private slots:
    void updateTimer();     // Обновление времени на экране
    void cancelSearch();    // Обработчик кнопки отмены

    void onTmpButtonClicked();
};

#endif // OPPONENTSEARCHWINDOW_H
