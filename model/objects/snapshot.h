#ifndef SNAPSHOT_H
#define SNAPSHOT_H

class Table;

class Snapshot
{
private:
    Table * table;

public:
    Snapshot(Table * table);

    Table * getTable() const;
};

#endif // SNAPSHOT_H
