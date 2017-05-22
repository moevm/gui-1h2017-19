#include "ball.h"
#include "../constants/constants.h"

#include <cmath>
#include <limits>

void Ball::recalculateAccel()
{
    using Constants::ACCELERATION;

    if (speed.getSize() == 0) {
        accel.setX(0);
        accel.setY(0);
        return;
    }

    accel.setX(speed.getX() / speed.getSize() * ACCELERATION);
    accel.setY(speed.getY() / speed.getSize() * ACCELERATION);
}

Ball::Ball(DoubleVector2D position,
           double radius,
           DoubleVector2D speed)
    : position(position),
      speed(speed),
      radius(radius)
{
    recalculateAccel();
}

DoubleVector2D Ball::getPosition() const
{
    return position;
}

void Ball::setPosition(DoubleVector2D position)
{
    this->position = position;
}

DoubleVector2D Ball::getSpeed() const
{
    return speed;
}

void Ball::setSpeed(DoubleVector2D speed)
{
    this->speed = speed;
    recalculateAccel();
}

double Ball::getRadius() const
{
    return radius;
}

bool Ball::moving() const
{
    return speed.getSize() != 0;
}

double Ball::timeToStop() const
{
    if (accel.getSize() == 0) {
        return std::numeric_limits<double>::infinity();
    }

    return speed.getSize() / accel.getSize();
}
