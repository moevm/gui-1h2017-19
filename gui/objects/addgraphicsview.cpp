#include "addgraphicsview.h"
#include "gui/ballswidget.h"

#include <QDebug>
#include <QMouseEvent>
#include <QPointF>

#define SCALE 500

AddGraphicsView::AddGraphicsView(QWidget *& widget)
    : QGraphicsView(widget),
      parentWidget(nullptr)
{}

void AddGraphicsView::setParentWidget(BallsWidget * parentWidget)
{
    this->parentWidget = parentWidget;
}

void AddGraphicsView::mouseDoubleClickEvent(QMouseEvent * event)
{
    QPoint point = event->pos();
    if (rect().contains(point)) {
        QPointF mousePoint = mapToScene(point);
        if (parentWidget != nullptr) {
            parentWidget->addBall(new QPointF(mousePoint.x() / SCALE,
                                              mousePoint.y() / SCALE));
        }
    }
}
