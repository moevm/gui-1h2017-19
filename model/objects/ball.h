#ifndef BALL_H
#define BALL_H


class Ball
{
private:
    double x;
    double y;

    double speedX;
    double speedY;

    double accelX;
    double accelY;

    double const radius;

    void recalculateAccel();

public:
    Ball(double x,
         double y,
         double radius,
         double speedX = 0,
         double speedY = 0);

    double getSpeedX() const;
    double getSpeedY() const;

    double getSpeed() const;
    double getRadius() const;

    void setSpeed(double speedX,
                  double speedY);
};

#endif // BALL_H
