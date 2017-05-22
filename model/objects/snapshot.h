#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <string>

class Table;

class Snapshot
{
private:
    std::string name;
    const Table *const table;
    double timestamp;

public:
    Snapshot(std::string name,
             Table * table,
             double timestamp);

    const Table * getTable() const;
    std::string getName() const;
    double getTimestamp() const;
};

#endif // SNAPSHOT_H
