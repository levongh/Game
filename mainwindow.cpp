#include "mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_pMainMenu = new MainMenu(this);
    connect(m_pMainMenu, SIGNAL(startGame()), this, SLOT(onStartGame()));
    connect(m_pMainMenu, SIGNAL(quitGame()), this, SLOT(onCloseGame()));

    m_pGameWidget = new GameWidget(this);
    m_pGameWidget->setEnabled(false);
    connect(m_pGameWidget, SIGNAL(openMainMenu()), this, SLOT(onOpenMainMenu()));

    QWidget* pCentralWdget = new QWidget(this);
    QVBoxLayout* pMainLayout = new QVBoxLayout(pCentralWdget);
    pMainLayout->addWidget(m_pMainMenu, 0, Qt::AlignTop);
    pMainLayout->addWidget(m_pGameWidget, 5);
    pMainLayout->setSpacing(3);
    pMainLayout->setContentsMargins(5,5,5,5);

    setCentralWidget(pCentralWdget);
    setMinimumSize(800, 500);
}

MainWindow::~MainWindow()
{

}

void MainWindow::onStartGame()
{
    m_pMainMenu->setVisible(false);
    m_pGameWidget->startGame();
}

void MainWindow::onCloseGame()
{
    MainWindow::close();
}

void MainWindow::onOpenMainMenu()
{
    m_pGameWidget->setEnabled(false);
    m_pMainMenu->setVisible(true);
}
