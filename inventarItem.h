#pragma once

#include <QLabel>
#include <QFrame>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE


class InventarItem : public QFrame
{
public:
    InventarItem(QWidget* parent);

    static QString inventarMimeType()
    {
        return QStringLiteral("application/x-dnditemdata");
    }

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    uint32_t m_count;
};
