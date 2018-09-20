#include <QHeaderView>
#include <QtWidgets>

#include "gametable.h"
#include "inventarItem.h"

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
    qDebug() << __FUNCTION__;
    if (event->mimeData()->hasFormat("application/x-dnditemdata"))
        event->accept();
    else
        event->ignore();
}

void GameTable::dragLeaveEvent(QDragLeaveEvent *event)
{
    qDebug() << __FUNCTION__;
    QTableWidget::dragLeaveEvent(event);
}

void GameTable::dragMoveEvent(QDragMoveEvent *event)
{
    qDebug() << __FUNCTION__;
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
    qDebug() << __FUNCTION__;
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
        ++m_indexToImage[index];
        qDebug() << m_indexToImage[index];

        if (event->source() == this) {
            //event->setDropAction(Qt::CopyAction);
            //event->accept();
        } else {
            //event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void GameTable::mousePressEvent(QMouseEvent *event)
{
    qDebug() << __FUNCTION__;
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
