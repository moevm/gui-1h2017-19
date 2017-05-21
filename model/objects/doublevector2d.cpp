#include "doublevector2d.h"

#include <cmath>

void DoubleVector2D::polarToRectangular()
{
    using std::sin;
    using std::cos;

    x = size * cos(angle);
    y = size * sin(angle);
}

void DoubleVector2D::rectangularToPolar()
{
    using std::sqrt;
    using std::pow;
    using std::atan2;

    size = sqrt(pow(x, 2) + pow(y, 2));
    angle = atan2(y, x);
}

DoubleVector2D::DoubleVector2D(double x,
                               double y)
    : x(x),
      y(y)
{
    rectangularToPolar();
}

double DoubleVector2D::getX() const
{
    return x;
}

void DoubleVector2D::setX(double value)
{
    x = value;
    rectangularToPolar();
}

double DoubleVector2D::getY() const
{
    return y;
}

void DoubleVector2D::setY(double value)
{
    y = value;
    rectangularToPolar();
}

double DoubleVector2D::getSize() const
{
    return size;
}

void DoubleVector2D::setSize(double value)
{
    size = value;
    polarToRectangular();
}

double DoubleVector2D::getAngle() const
{
    return angle;
}

void DoubleVector2D::setAngle(double value)
{
    angle = value;
    polarToRectangular();
}
