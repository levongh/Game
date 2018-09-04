#pragma once

#include <QMainWindow>
#include "mainmenu.h"
#include "gamewidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

private slots:
    void onStartGame();
    void onCloseGame();
    void onOpenMainMenu();

private:
    MainMenu* m_pMainMenu;
    GameWidget* m_pGameWidget;
};
