#include "snapshot.h"
#include "table.h"

Snapshot::Snapshot(Table * table, double timestamp)
    : table(new Table(*table)),
      timestamp(timestamp)
{}

Table * Snapshot::getTable() const
{
    return table;
}
