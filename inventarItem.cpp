#include <QtWidgets>

#include "inventarItem.h"

InventarItem::InventarItem(QWidget* parent)
    : QFrame(parent)
{
    setMinimumSize(128, 128);
    setAcceptDrops(true);

    QLabel *appleIcon = new QLabel(this);
    appleIcon->setPixmap(QPixmap(":images/apple.png"));
    setAttribute(Qt::WA_DeleteOnClose);
}

void InventarItem::dragEnterEvent(QDragEnterEvent *event)
{
    QFrame::dragEnterEvent(event);
}

void InventarItem::dragMoveEvent(QDragMoveEvent *event)
{
    QFrame::dragMoveEvent(event);
}

void InventarItem::dropEvent(QDropEvent *event)
{
    QFrame::dropEvent(event);
}

void InventarItem::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child) {
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
