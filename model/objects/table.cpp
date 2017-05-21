#include "table.h"
#include "ball.h"

#include <algorithm>

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

bool Table::addBall(Ball * /*ball*/)
{

    // TODO: Подготовить добавление шара на стол, учитывая коллизии с другими
    // шарами

    return false;
}

Table::~Table()
{
    std::for_each(balls.begin(),
                  balls.end(),
                  [](Ball * ball) {
        delete ball;
    });
}
