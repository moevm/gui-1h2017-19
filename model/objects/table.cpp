#include "table.h"
#include "ball.h"
#include "../utils/ballsutils.h"

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

Table::~Table()
{
    std::for_each(balls.begin(),
                  balls.end(),
                  [](Ball * ball) {
        delete ball;
    });
}
