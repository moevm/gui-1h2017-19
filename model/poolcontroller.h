#ifndef POOLCONTROLLER_H
#define POOLCONTROLLER_H

class Table;

class PoolController
{
private:
    Table * table;

    enum Status {
        BALL_STOPPED,
        WALL_COLLISION,
        BALLS_COLLISION
    };

    double timeToStop() const;

public:
    PoolController();

    void calculateHit();
};

#endif // POOLCONTROLLER_H
