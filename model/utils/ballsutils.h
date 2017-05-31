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

    static bool upCollisionWithTable(const Ball * ball,
                                     const Table * table);
    static bool downCollisionWithTable(const Ball * ball,
                                       const Table * table);
    static bool leftCollisionWithTable(const Ball * ball,
                                       const Table * table);
    static bool rightCollisionWithTable(const Ball * ball,
                                        const Table * table);

    static double prefferedStepTime(const Ball * first,
                                    const Ball * second);

public:
    static double distance(const Ball * first,
                           const Ball * second);

    static bool collision(Ball * first,
                          Ball * second);

    static bool collisionWithTable(Ball * ball,
                                   Table * table);

    static bool horizontalCollisionWithTable(const Ball * ball,
                                             const Table * table);
    static bool verticalCollisionWithTable(const Ball * ball,
                                           const Table * table);

    static double timeToCollision(const Ball * first,
                                  const Ball * second);
    static double timeToCollisionWithTable(const Ball * ball,
                                           const Table * table);

    static void recalculateCollision(Ball * first,
                                     Ball * second);
};

#endif // BALLSCOLLISIONS_H
