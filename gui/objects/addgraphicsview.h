#ifndef ADDGRAPHICSVIEW_H
#define ADDGRAPHICSVIEW_H

#include <QGraphicsView>

class BallsWidget;

class AddGraphicsView : public QGraphicsView
{
public:
    AddGraphicsView(QWidget *& widget);
    void setParentWidget(BallsWidget * parentWidget);

protected:
    void mouseDoubleClickEvent(QMouseEvent * event);

private:
    BallsWidget * parentWidget;
};

#endif // ADDGRAPHICSVIEW_H
