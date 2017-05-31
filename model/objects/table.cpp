#include "table.h"
#include "ball.h"
#include "../utils/ballsutils.h"

#include <algorithm>
#include <limits>
#include <QDebug>

std::set<Ball *> Table::getBalls() const
{
    return balls;
}

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
    if (balls.size() >= 6) {
        return false;
    }

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

void Table::goToNextStep(double timeDiff)
{
    for (Ball * first : balls) {
        for (Ball * second : balls) {
            if (first->getId() != second->getId()) {
                qDebug() << "Before dist:" << BallsUtils::distance(first, second);
            }
        }
    }
    for (Ball * ball : balls) {
        ball->goToNextStep(timeDiff);
    }
    for (Ball * first : balls) {
        for (Ball * second : balls) {
            if (first->getId() != second->getId()) {
                qDebug() << "After dist:" << BallsUtils::distance(first, second);
            }
        }
    }
}

double Table::shortestTimeToStop() const
{
    double time = std::numeric_limits<double>::infinity();

    std::for_each(balls.begin(),
                  balls.end(),
                  [&](Ball * ball) {
        time = std::min(time, ball->timeToStop());
    });

    return time;
}

double Table::shortestTimeToWall() const
{
    double time = std::numeric_limits<double>::infinity();

    std::for_each(balls.begin(),
                  balls.end(),
                  [&](Ball * ball) {
        time = std::min(time,
                        BallsUtils::timeToCollisionWithTable(ball, this));
    });

    return time;
}

double Table::shortestTimeToCollision() const
{
    double time = std::numeric_limits<double>::infinity();

    for (const Ball * first : balls) {
        for (const Ball * second : balls) {
            if (first->getId() != second->getId()) {
                time = std::min(time,
                                BallsUtils::timeToCollision(first, second));
            }
        }
    }

    return time;
}

void Table::recalculateWallCollision()
{
    std::for_each(balls.begin(),
                  balls.end(),
                  [&](Ball * ball) {
        if (BallsUtils::horizontalCollisionWithTable(ball, this)) {
            DoubleVector2D speed = ball->getSpeed();
            speed.setX(-speed.getX());
            ball->setSpeed(speed);
        }

        if (BallsUtils::verticalCollisionWithTable(ball, this)) {
            DoubleVector2D speed = ball->getSpeed();
            speed.setY(-speed.getY());
            ball->setSpeed(speed);
        }
    });
}

void Table::recalculateBallCollision()
{
    for(Ball * first : balls) {
        for (Ball * second : balls) {
            auto id1 = first->getId();
            auto id2 = second->getId();
            if (id1 != id2) {
                bool c = BallsUtils::collision(first, second);
                if (c) {
                    BallsUtils::recalculateCollision(first, second);
                }
            }
        }
    }
}

Table::~Table()
{
    std::for_each(balls.begin(),
                  balls.end(),
                  [](Ball * ball) {
        delete ball;
    });
}
