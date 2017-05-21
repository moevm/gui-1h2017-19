#include "ball.h"
#include "../constants/constants.h"

#include <cmath>

void Ball::recalculateAccel()
{
    using Constants::ACCELERATION;

    double speed = getSpeed();

    if (speed == 0) {
        accelX = 0;
        accelY = 0;

        return;
    }

    accelX = speedX / speed * ACCELERATION;
    accelY = speedY / speed * ACCELERATION;
}

Ball::Ball(double x,
           double y,
           double radius,
           double speedX,
           double speedY)
    : x(x),
      y(y),
      speedX(speedX),
      speedY(speedY),
      radius(radius)
{
    recalculateAccel();
}

double Ball::getSpeedX() const
{
    return speedX;
}

double Ball::getSpeedY() const
{
    return speedY;
}

double Ball::getSpeed() const
{
    using std::sqrt;
    using std::pow;

    return sqrt(pow(speedX, 2) +
                pow(speedY, 2));
}

double Ball::getRadius() const
{
    return radius;
}

void Ball::setSpeed(double speedX, double speedY)
{
    this->speedX = speedX;
    this->speedY = speedY;

    recalculateAccel();
}
