#include "table.h"
#include "ball.h"
#include "../utils/ballsutils.h"

#include <algorithm>

Table::Table(double width,
             double height)
    : width(width),
      height(height)
{}

Table::Table(Table const & table)
    : width(table.width),
      height(table.height)
{
    std::for_each(table.balls.begin(),
                  table.balls.end(),
                  [&](Ball * ball) {
        balls.insert(new Ball(*ball));
    });
}

double Table::getWidth() const
{
    return width;
}

double Table::getHeight() const
{
    return height;
}

bool Table::addBall(Ball * ball)
{

    if (balls.count(ball)) {
        return false;
    }

    if (BallsUtils::collisionWithTable(ball, this)) {
        return false;
    }

    bool canAdd = true;
    std::for_each(balls.begin(),
                  balls.end(),
                  [&](Ball * anotherBall) {
        if (BallsUtils::collision(ball, anotherBall)) {
            canAdd = false;
        }
    });

    if (canAdd) {
        balls.insert(ball);
    }

    return canAdd;
}

bool Table::hasMoving() const
{
    bool has = false;

    std::for_each(balls.begin(),
                  balls.end(),
                  [&](Ball * ball) {
        has = has || ball->moving();
    });

    return has;
}

Table::~Table()
{
    std::for_each(balls.begin(),
                  balls.end(),
                  [](Ball * ball) {
        delete ball;
    });
}
