#include "ballgui.h"
#include "model/objects/ball.h"
#include "model/objects/doublevector2d.h"

#include <QBrush>
#include <QDebug>

BallGUI::BallGUI()
    : ball(new Ball(DoubleVector2D(), 0.034))
{
    setRect(getX() - getRadius(),
            getY() - getRadius(),
            ball->getRadius() * 200,
            ball->getRadius() * 200);
    setBrush(QBrush(QColor(Qt::white)));
    setFlag(QGraphicsItem::ItemIsMovable, true);
}

double BallGUI::getX() const
{
    return ball->getPosition().getX() * 100;
}

double BallGUI::getY() const
{
    return ball->getPosition().getY() * 100;
}

double BallGUI::getRadius() const
{
    return ball->getRadius() * 100;
}

Ball *BallGUI::getBall() const
{
    return ball;
}

void BallGUI::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
    QGraphicsItem::mouseMoveEvent(event);
    qDebug() << this->pos().x() << " " << this->pos().y();
}
