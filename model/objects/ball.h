#ifndef BALL_H
#define BALL_H

#include "doublevector2d.h"

class Ball
{
private:
    DoubleVector2D position;
    DoubleVector2D speed;
    DoubleVector2D accel;

    double const radius;

    void recalculateAccel();

public:
    Ball(DoubleVector2D position,
         DoubleVector2D speed = DoubleVector2D());

    DoubleVector2D getPosition() const;
    void setPosition(DoubleVector2D position);

    DoubleVector2D getSpeed() const;
    void setSpeed(DoubleVector2D speed);

    DoubleVector2D getAccel() const;

    double getRadius() const;

    bool moving() const;

    double timeToStop() const;

    void goToNextStep(double timeDiff);
};

#endif // BALL_H
