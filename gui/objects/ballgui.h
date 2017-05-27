#ifndef BALLGUI_H
#define BALLGUI_H

#include <QGraphicsEllipseItem>

class Ball;

class BallGUI : public QGraphicsEllipseItem
{
public:
    BallGUI();

    double getX() const;
    double getY() const;
    double getRadius() const;
    Ball * getBall() const;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);

private:
    Ball * ball;
};

#endif // BALLGUI_H
