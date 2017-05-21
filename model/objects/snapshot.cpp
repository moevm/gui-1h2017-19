#include "snapshot.h"
#include "table.h"

Snapshot::Snapshot(Table * table)
    : table(new Table(*table))
{}

Table * Snapshot::getTable() const
{
    return table;
}
