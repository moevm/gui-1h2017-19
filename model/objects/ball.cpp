#include "ball.h"
#include "model/constants/constants.h"

#include <cmath>
#include <limits>
#include <QDebug>

unsigned long Ball::maxId = 0;

void Ball::recalculateAccel()
{

    if (speed.getSize() == 0) {
        accel.setX(0);
        accel.setY(0);
        return;
    }

    const double ACCELERATION = Constants::getAccel();
    accel.setX(speed.getX() / speed.getSize() * ACCELERATION);
    accel.setY(speed.getY() / speed.getSize() * ACCELERATION);
}

Ball::Ball(DoubleVector2D position,
           DoubleVector2D speed)
    : id(maxId++),
      position(position),
      speed(speed),
      radius(0.034)
{
    qDebug() << "New ball, pos: " << position.getX() << " " << position.getY();
    recalculateAccel();
}

DoubleVector2D Ball::getPosition() const
{
    return position;
}

void Ball::setPosition(DoubleVector2D position)
{
    this->position = position;
    qDebug() << "Ball moved, pos: " << position.getX()
             << " " << position.getY();
}

DoubleVector2D Ball::getSpeed() const
{
    return speed;
}

void Ball::setSpeed(DoubleVector2D speed)
{
    qDebug() << "Ball speed changed: " << speed.getSize() << " " << speed.getAngle();
    this->speed = speed;
    if (speed.getSize() < 1e-2) {
        this->speed.setSize(0);
    }
    recalculateAccel();
}

DoubleVector2D Ball::getAccel() const
{
    return accel;
}

double Ball::getRadius() const
{
    return radius;
}

bool Ball::moving() const
{
    return speed.getSize() != 0;
}

unsigned long Ball::getId() const
{
    return id;
}

double Ball::timeToStop() const
{
    if (accel.getSize() == 0) {
        return std::numeric_limits<double>::infinity();
    }

    return speed.getSize() / accel.getSize();
}

void Ball::goToNextStep(double timeDiff)
{
    position.setX(position.getX() + speed.getX() * timeDiff +
                  accel.getX() * timeDiff * timeDiff / 2);
    speed.setX(speed.getX() + accel.getX() * timeDiff);

    position.setY(position.getY() + speed.getY() * timeDiff +
                  accel.getY() * timeDiff * timeDiff / 2);
    speed.setY(speed.getY() + accel.getY() * timeDiff);

    recalculateAccel();
}
