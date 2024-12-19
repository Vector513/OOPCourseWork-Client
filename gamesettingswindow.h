#ifndef GAMESETTINGSWINDOW_H
#define GAMESETTINGSWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QGroupBox>
#include <QPushButton>

class GameSettingsWindow : public QWidget {
    Q_OBJECT

public:
    explicit GameSettingsWindow(QWidget *parent = nullptr);

signals:
    void startNetworkGame();  // Сигнал для начала сетевой игры
};

#endif // GAMESETTINGSWINDOW_H
