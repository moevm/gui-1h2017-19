#ifndef BALLGUI_H
#define BALLGUI_H

#include <QGraphicsEllipseItem>

class Ball;
class TableGUI;

class BallGUI : public QGraphicsEllipseItem
{
public:
    BallGUI(Ball * ball, TableGUI * table);

    double getX() const;
    double getY() const;
    double getRadius() const;
    Ball * getBall() const;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

private:
    Ball * ball;
    TableGUI * table;
};

#endif // BALLGUI_H
