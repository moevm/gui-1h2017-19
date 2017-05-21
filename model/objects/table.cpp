#include "table.h"

Table::Table(double width,
             double height)
    : width(width),
      height(height)
{}

double Table::getWidth() const
{
    return width;
}

double Table::getHeight() const
{
    return height;
}
