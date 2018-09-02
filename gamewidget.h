#pragma once

#include <QWidget>
#include <QTableWidget>

#include "inventarItem.h"

#include <map>

class GameTable : public QTableWidget
{
    Q_OBJECT

public:
    GameTable(QWidget* parent);
    virtual ~GameTable();

public:
    void mousePressEvent(QMouseEvent *event) override;

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    std::map<QModelIndex, unsigned> m_indexToImage;
};

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    GameWidget(QWidget* parent = 0);
    virtual ~GameWidget();

    void mousePressEvent(QMouseEvent* event) override;

public:
    void startGame();

signals:
    void openMainMenu();

private:
    GameTable* m_pTable;
    InventarItem* m_pCurrFruit;

};
