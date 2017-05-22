#ifndef POOLCONTROLLER_H
#define POOLCONTROLLER_H

#include <vector>

class Table;
class Snapshot;

class PoolController
{
private:
    Table * table = nullptr;

    std::vector<Snapshot *> history;

    double timeToStop() const;
    double timeToWallCollision() const;

public:
    void setTable(Table * table);
    void calculateHit();

    ~PoolController();
};

#endif // POOLCONTROLLER_H
