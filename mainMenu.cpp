#include "mainMenu.h"

#include <QPushButton>
#include <QHBoxLayout>

MainMenu::MainMenu(QWidget* parent /*= 0*/)
{
    QPushButton* pStartGameBtn = new QPushButton("Start", this);
    connect(pStartGameBtn, SIGNAL(clicked(bool)), this, SIGNAL(startGame()));
    QPushButton* pQuitGameBtn = new QPushButton("Quit", this);
    connect(pQuitGameBtn, SIGNAL(clicked(bool)), this, SIGNAL(quitGame()));

    QHBoxLayout* pLayout = new QHBoxLayout;
    pLayout->addStretch(2);
    pLayout->addWidget(pStartGameBtn);
    pLayout->addStretch(1);
    pLayout->addWidget(pQuitGameBtn);
    pLayout->addStretch(2);
    setLayout(pLayout);
}

MainMenu::~MainMenu()
{
}
