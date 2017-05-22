#ifndef POOLCONTROLLER_H
#define POOLCONTROLLER_H

class Table;

class PoolController
{
private:
    Table * table;

public:
    PoolController();

    void calculateHit();
};

#endif // POOLCONTROLLER_H
