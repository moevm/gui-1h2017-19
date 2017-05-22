#ifndef SNAPSHOT_H
#define SNAPSHOT_H

class Table;

class Snapshot
{
private:
    const Table *const table;
    double timestamp;

public:
    Snapshot(Table * table,
             double timestamp);

    const Table * getTable() const;
};

#endif // SNAPSHOT_H
