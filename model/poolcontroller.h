#ifndef POOLCONTROLLER_H
#define POOLCONTROLLER_H

#include "constants/constants.h"

#include <vector>

class Table;
class Snapshot;
class Ball;

class PoolController
{
private:
    Table * table = nullptr;

    std::vector<Snapshot *> history;

    double timeToStop() const;
    double timeToWallCollision() const;
    void saveToHistory(double calculationTime,
                       enum Constants::GameStatus status);

public:
    void setTable(Table * table);
    void calculateHit();
    bool addBall(Ball * ball);

    ~PoolController();
};

#endif // POOLCONTROLLER_H
