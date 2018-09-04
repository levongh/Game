#include <QGridLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QtWidgets>
#include <utility>

#include "gamewidget.h"

GameWidget::GameWidget(QWidget* parent)
    : QWidget(parent)
{
    m_pTable = new GameTable(this);

    m_pCurrFruit = new InventarItem(this);
    QPushButton* pOpenMenuBtn = new QPushButton("Open Menu", this);
    connect(pOpenMenuBtn, SIGNAL(clicked(bool)), this, SIGNAL(openMainMenu()));

    QGridLayout* pGrid = new QGridLayout;
    pGrid->addWidget(m_pTable, 0, 0, 6, 6);
    pGrid->addWidget(m_pCurrFruit, 2, 8, 2, 2, Qt::AlignCenter);
    pGrid->addWidget(pOpenMenuBtn, 5, 8, 1, 2, Qt::AlignCenter);
    setLayout(pGrid);
}

void GameWidget::startGame()
{
    m_pTable->clearContents();
    setEnabled(true);
}

GameWidget::~GameWidget()
{
}
