#ifndef BALLGUI_H
#define BALLGUI_H

#include <QGraphicsEllipseItem>

class Ball;

class BallGUI : public QGraphicsEllipseItem
{
public:
    BallGUI(Ball * ball);

    double getX() const;
    double getY() const;
    double getRadius() const;
    Ball * getBall() const;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

private:
    Ball * ball;
};

#endif // BALLGUI_H
