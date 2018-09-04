#pragma once

#include <QWidget>
#include <QTableWidget>

#include <map>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class GameTable : public QTableWidget
{
    //Q_OBJECT

public:
    GameTable(QWidget* parent = 0);
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
