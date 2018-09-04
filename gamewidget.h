#pragma once

#include "gametable.h"
#include "inventarItem.h"

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    GameWidget(QWidget* parent = 0);
    virtual ~GameWidget();

public:
    void startGame();

signals:
    void openMainMenu();

private:
    GameTable* m_pTable;
    InventarItem* m_pCurrFruit;

};
