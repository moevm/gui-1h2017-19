#ifndef POOLCONTROLLER_H
#define POOLCONTROLLER_H

#include <vector>

class Table;
class Snapshot;

namespace Constants {
enum GameStatus;
}

class PoolController
{
private:
    Table * table = nullptr;

    std::vector<Snapshot *> history;

    double timeToStop() const;
    double timeToWallCollision() const;
    void saveToHistory(enum Constants::GameStatus status,
                       calculationTime);

public:
    void setTable(Table * table);
    void calculateHit();

    ~PoolController();
};

#endif // POOLCONTROLLER_H
