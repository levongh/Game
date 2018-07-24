#pragma once

#include <QWidget>

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    MainMenu(QWidget* parent = 0);
    virtual ~MainMenu();

signals:
    void startGame();
    void quitGame();
};
