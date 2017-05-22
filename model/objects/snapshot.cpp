#include "snapshot.h"
#include "table.h"

Snapshot::Snapshot(Table * table, double timestamp)
    : table(new Table(*table)),
      timestamp(timestamp)
{}

const Table * Snapshot::getTable() const
{
    return table;
}
