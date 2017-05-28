#include "ballgui.h"
#include "model/objects/ball.h"
#include "model/objects/doublevector2d.h"
#include "tablegui.h"

#include <QBrush>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QWidget>
#include <cmath>

#define SCALE 500

BallGUI::BallGUI(Ball * ball, TableGUI * table)
    : ball(ball),
      table(table)
{
    setRect(getX() - getRadius(),
            getY() - getRadius(),
            ball->getRadius() * 2 * SCALE,
            ball->getRadius() * 2 * SCALE);
    setBrush(QBrush(QColor(Qt::white)));
    setFlag(QGraphicsItem::ItemIsMovable, true);
}

double BallGUI::getX() const
{
    return ball->getPosition().getX() * SCALE;
}

double BallGUI::getY() const
{
    return ball->getPosition().getY() * SCALE;
}

double BallGUI::getRadius() const
{
    return ball->getRadius() * SCALE;
}

Ball *BallGUI::getBall() const
{
    return ball;
}

unsigned long BallGUI::getId() const
{
    return ball->getId();
}

void BallGUI::updateBall(Ball * ball)
{
    this->ball->setPosition(ball->getPosition());
    this->ball->setSpeed(ball->getSpeed());
    double radius = rect().height() / 2.0;
    double xPos = rect().x() + radius;
    double yPos = rect().y() + radius;
    setPos(ball->getPosition().getX() * SCALE - xPos,
           ball->getPosition().getY() * SCALE - yPos);
    update();
}

void BallGUI::paint(QPainter * painter,
                    const QStyleOptionGraphicsItem * option,
                    QWidget * widget)
{
    QGraphicsEllipseItem::paint(painter, option, widget);
    DoubleVector2D ballSpeed = ball->getSpeed();
    if (ball->getSpeed().getSize()) {
        setToolTip(QString::number(ballSpeed.getSize()) + " м/с");
        double radius = rect().height() / 2.0;
        double xPos = rect().x() + radius;
        double yPos = rect().y() + radius;

        double angle = ball->getSpeed().getAngle();
        double speed = ball->getSpeed().getSize();
        double xOffset = xPos + speed * radius * cos(angle);
        double yOffset = yPos + speed * radius * sin(angle);

        painter->drawLine(xPos, yPos,
                          xOffset, yOffset);
        painter->drawLine(xPos + 1, yPos,
                          xOffset + 1, yOffset);
        painter->drawLine(xPos, yPos + 1,
                          xOffset, yOffset + 1);
        painter->drawLine(xPos + 1, yPos + 1,
                          xOffset + 1, yOffset + 1);
    } else {
        setToolTip("");
    }
    widget->update();
}

void BallGUI::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
    if (!(flags() & QGraphicsItem::ItemIsMovable))
        return;
    QGraphicsItem::mouseMoveEvent(event);
    DoubleVector2D position;
    position.setX(event->scenePos().x() / SCALE);
    position.setY(event->scenePos().y() / SCALE);
    ball->setPosition(position);
}

void BallGUI::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    if (event->button() == Qt::RightButton) {
        qDebug() << "Item selected";
        table->setSelectedBall(this);
    } else {
        QGraphicsEllipseItem::mousePressEvent(event);
    }
}
