#ifndef SNAPSHOT_H
#define SNAPSHOT_H

class Table;

class Snapshot
{
private:
    Table * table;
    double timestamp;

public:
    Snapshot(Table * table,
             double timestamp);

    Table * getTable() const;
};

#endif // SNAPSHOT_H
