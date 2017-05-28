#include "ballgui.h"
#include "model/objects/ball.h"
#include "model/objects/doublevector2d.h"
#include "tablegui.h"

#include <QBrush>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

BallGUI::BallGUI(Ball * ball, TableGUI * table)
    : ball(ball),
      table(table)
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

void BallGUI::paint(QPainter * painter,
                    const QStyleOptionGraphicsItem * option,
                    QWidget * widget)
{
    QGraphicsEllipseItem::paint(painter, option, widget);

    DoubleVector2D ballSpeed = ball->getSpeed();
    setToolTip(QString::number(ballSpeed.getSize()) + " м/с");
    if (ballSpeed.getSize() != 0) {
        // TODO: отрисовать линию направления скорости
    }
}

void BallGUI::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
    if (!(flags() & QGraphicsItem::ItemIsMovable))
        return;
    QGraphicsItem::mouseMoveEvent(event);
    DoubleVector2D position;
    position.setX(event->scenePos().x() / 100);
    position.setY(event->scenePos().y() / 100);
    ball->setPosition(position);
}

void BallGUI::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    if (event->button() == Qt::RightButton) {
        table->setSelectedBall(this);
    } else {
        QGraphicsEllipseItem::mousePressEvent(event);
    }
}
