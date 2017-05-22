#ifndef BALLSCOLLISIONS_H
#define BALLSCOLLISIONS_H

class Ball;
class Table;

class BallsUtils
{
private:
    static double timeByDSA(double dist,
                            double speed,
                            double accel);

    static double timeBySA(double speed,
                           double accel);

public:
    static double distance(Ball * first,
                           Ball * second);

    static bool collision(Ball * first,
                          Ball * second);

    static bool collisionWithTable(Ball * ball,
                                   Table * table);

    static double timeToCollisionWithTable(Ball * ball,
                                           Table * table);
};

#endif // BALLSCOLLISIONS_H
