#ifndef BALLSCOLLISIONS_H
#define BALLSCOLLISIONS_H

class Ball;
class Table;

class BallsUtils
{
public:
    static double distance(Ball * first,
                           Ball * second);

    static bool collision(Ball * first,
                          Ball * second);

    static bool collisionWithTable(Ball * ball,
                                   Table * table);
};

#endif // BALLSCOLLISIONS_H
