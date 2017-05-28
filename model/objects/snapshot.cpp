#include "snapshot.h"
#include "table.h"

std::string Snapshot::getName() const
{
    return name;
}

double Snapshot::getTimestamp() const
{
    return timestamp;
}

Snapshot::Snapshot(std::string name,
                   Table * table,
                   double timestamp)
    : name(name),
      table(new Table(*table)),
      timestamp(timestamp)
{}

const Table * Snapshot::getTable() const
{
    return table;
}
