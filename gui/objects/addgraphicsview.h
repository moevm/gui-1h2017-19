#ifndef ADDGRAPHICSVIEW_H
#define ADDGRAPHICSVIEW_H

#include <QGraphicsView>

class AddGraphicsView : public QGraphicsView
{
public:
    AddGraphicsView(QWidget *& widget);

signals:
    doubleClick(QPointF point);

protected:
    void mouseDoubleClickEvent(QMouseEvent * event);
};

#endif // ADDGRAPHICSVIEW_H
