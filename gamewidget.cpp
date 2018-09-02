#include <QGridLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QtWidgets>
#include <utility>


#include "gameWidget.h"


GameTable::GameTable(QWidget* parent)
    : QTableWidget(parent)
{
    setRowCount(3);
    setColumnCount(3);
    horizontalHeader()->setVisible(false);
    horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
    verticalHeader()->setVisible(false);
    verticalHeader()->setSectionResizeMode( QHeaderView::Stretch );
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setAcceptDrops(true);
}

GameTable::~GameTable()
{

}

void GameTable::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata"))
        event->accept();
    else
        event->ignore();
}

void GameTable::dragLeaveEvent(QDragLeaveEvent *event)
{
    QTableWidget::dragLeaveEvent(event);
}

void GameTable::dragMoveEvent(QDragMoveEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    if (event->mimeData()->hasFormat(InventarItem::inventarMimeType())) {
        event->setDropAction(Qt::CopyAction);
        event->accept();
    } else {
        event->ignore();
    }
    update(index);
}

void GameTable::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat(InventarItem::inventarMimeType())) {
        QByteArray itemData = event->mimeData()->data(InventarItem::inventarMimeType());
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        QPixmap pixmap;
        dataStream >> pixmap;

        QLabel *newIcon = new QLabel(this);
        newIcon->setPixmap(pixmap);
        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);

        QModelIndex index = indexAt(event->pos());
        setCellWidget(index.row(), index.column(), newIcon);
        auto mapIter = m_indexToImage.find(index);
        if (mapIter != m_indexToImage.end()) {
            m_indexToImage.insert(std::make_pair<QModelIndex, unsigned>(std::move(index), std::move(++mapIter->second)));
        } else {
            m_indexToImage.insert(std::make_pair<QModelIndex, unsigned>(std::move(index), 1));
        }

        if (event->source() == this) {
            event->setDropAction(Qt::CopyAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void GameTable::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = dynamic_cast<QLabel*>(childAt(event->pos()));
    if (!child) {
        QTableWidget::mousePressEvent(event);
        return;
    }
    QPixmap pixmap = *child->pixmap();
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();

    child->setPixmap(tempPixmap);

    if (drag->exec(Qt::MoveAction) == Qt::MoveAction) {
        child->setPixmap(pixmap);
    } else {
        child->show();
        child->setPixmap(pixmap);
    }
}

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

void GameWidget::mousePressEvent(QMouseEvent *event)
{
}

GameWidget::~GameWidget()
{
}
