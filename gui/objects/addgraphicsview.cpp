#include "addgraphicsview.h"
#include <QDebug>
#include <QMouseEvent>

AddGraphicsView::AddGraphicsView(QWidget *& widget)
    : QGraphicsView(widget)
{
}

void AddGraphicsView::mouseDoubleClickEvent(QMouseEvent * event)
{
    QPoint point = event->pos();
    if (rect().contains(point)) {
        QPointF mousePoint = mapToScene(point);
        emit doubleClick(mousePoint);
    }
}
