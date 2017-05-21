#ifndef BALL_H
#define BALL_H


class Ball
{
private:
    double x;
    double y;

    double speed_x;
    double speed_y;

    double accel_x;
    double accel_y;

    double radius;

    void recalculateAccel();

public:
    Ball(double x,
         double y,
         double radius,
         double speed_x = 0,
         double speed_y = 0);

    double getSpeed() const;
    double getRadius() const;
};

#endif // BALL_H
