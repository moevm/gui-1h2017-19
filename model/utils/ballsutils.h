#ifndef BALLSCOLLISIONS_H
#define BALLSCOLLISIONS_H

class Ball;

class BallsUtils
{
public:
    static double distance(Ball * first,
                           Ball * second);

    static bool collision(Ball * first,
                          Ball * second);
};

#endif // BALLSCOLLISIONS_H
