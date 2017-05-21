#include "ball.h"
#include "../constants/constants.h"

#include <cmath>

void Ball::recalculateAccel()
{
    using Constants::ACCELERATION;

    double speed = getSpeed();

    accel_x = speed_x / speed * ACCELERATION;
    accel_y = speed_y / speed * ACCELERATION;
}

Ball::Ball(double x,
           double y,
           double radius,
           double speed_x,
           double speed_y)
    : x(x),
      y(y),
      speed_x(speed_x),
      speed_y(speed_y),
      radius(radius)
{
    recalculateAccel();
}

double Ball::getSpeed() const
{
    using std::sqrt;
    using std::pow;

    return sqrt(pow(speed_x, 2) +
                pow(speed_y, 2));
}

double Ball::getRadius() const
{
    return radius;
}
