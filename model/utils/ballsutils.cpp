#include "ballsutils.h"
#include "../objects/ball.h"
#include "../objects/table.h"

#include <cmath>
#include <limits>
#include <algorithm>
#include <cassert>

double BallsUtils::timeByDSA(double dist, double speed, double accel)
{
    assert(dist >= 0);
    assert(speed > 0);
    assert(accel < 0);

    double timeToStop = timeBySA(speed, accel);
    double distToStop = speed * timeToStop +
                        accel * std::pow(timeToStop, 2) / 2;

    if (distToStop < dist) {
        return std::numeric_limits<double>::infinity();
    }

    double discriminant = 4 * std::pow(speed, 2) + 8 * accel * dist;
    assert(discriminant >= 0);

    using std::min;
    using std::sqrt;
    double neg = (-2 * speed - sqrt(discriminant)) / (2 * accel);
    double pos = (-2 * speed + sqrt(discriminant)) / (2 * accel);
    double time = min(neg, pos);
    if (pos < 0) {
        time = neg;
    }
    assert(time >= 0);

    return time;
}

double BallsUtils::timeBySA(double speed, double accel)
{
    assert(speed > 0);
    assert(accel < 0);

    return std::abs(speed / accel);
}

double BallsUtils::distance(Ball * first,
                            Ball * second)
{
    using std::sqrt;
    using std::pow;

    double firstX = first->getPosition().getX();
    double firstY = first->getPosition().getY();

    double secondX = second->getPosition().getX();
    double secondY = second->getPosition().getY();

    return sqrt(pow(firstX - secondX, 2) +
                pow(firstY - secondY, 2));
}

bool BallsUtils::collision(Ball * first,
                           Ball * second)
{
    return distance(first, second) <= first->getRadius() + second->getRadius();
}

bool BallsUtils::collisionWithTable(Ball * ball,
                                    Table * table)
{
    double ballX = ball->getPosition().getX();
    double ballY = ball->getPosition().getY();
    double ballRadius = ball->getRadius();

    double width = table->getWidth();
    double height = table->getHeight();

    using std::abs;

    return (width - ballX) <= ballRadius ||
            (height - ballY) <= ballRadius ||
            (ballX) <= ballRadius ||
            (ballY) <= ballRadius;
}

bool BallsUtils::horizontalCollisionWithTable(const Ball * ball,
                                              const Table * table)
{
    return leftCollisionWithTable(ball, table) ||
            rightCollisionWithTable(ball, table);
}

bool BallsUtils::verticalCollisionWithTable(const Ball * ball,
                                            const Table * table)
{
    return upCollisionWithTable(ball, table) ||
            downCollisionWithTable(ball, table);
}

bool BallsUtils::upCollisionWithTable(const Ball * ball,
                                      const Table * table)
{
    using std::abs;

    return abs(ball->getPosition().getY() - table->getHeight())
            <= ball->getRadius() + 10e-9;
}

bool BallsUtils::downCollisionWithTable(const Ball * ball,
                                        const Table * /*table*/)
{
    using std::abs;

    return abs(ball->getPosition().getY()) <= ball->getRadius() + 10e-9;
}

bool BallsUtils::leftCollisionWithTable(const Ball * ball,
                                        const Table * /*table*/)
{
    using std::abs;

    return abs(ball->getPosition().getX()) <= ball->getRadius() + 10e-9;
}

bool BallsUtils::rightCollisionWithTable(const Ball * ball,
                                         const Table * table)
{
    using std::abs;

    return abs(ball->getPosition().getX() - table->getWidth())
            <= ball->getRadius() + 10e-9;
}

double BallsUtils::timeToCollisionWithTable(const Ball * ball,
                                            const Table * table)
{
    if (ball->getSpeed().getSize() == 0) {
        return std::numeric_limits<double>::infinity();
    }

    double xDistance, yDistance;
    double xSpeed, ySpeed;
    double xAccel, yAccel;

    if (ball->getSpeed().getX() > 0) {
        xDistance = table->getWidth() - ball->getPosition().getX() - ball->getRadius();
        xSpeed = ball->getSpeed().getX();
        xAccel = ball->getAccel().getX();
    } else {
        xDistance = ball->getPosition().getX() - ball->getRadius();
        xSpeed = -ball->getSpeed().getX();
        xAccel = -ball->getAccel().getX();
    }

    if (ball->getSpeed().getY() > 0) {
        yDistance = table->getHeight() - ball->getPosition().getY() - ball->getRadius();
        ySpeed = ball->getSpeed().getY();
        yAccel = ball->getAccel().getY();
    } else {
        yDistance = ball->getPosition().getY() - ball->getRadius();
        ySpeed = -ball->getSpeed().getY();
        yAccel = -ball->getAccel().getY();
    }

    double xTime = std::numeric_limits<double>::infinity();
    double yTime = std::numeric_limits<double>::infinity();

    if (ball->getSpeed().getX()) {
        assert(xDistance >= 0);
        assert(xSpeed > 0);
        assert(xAccel < 0);


        xTime = std::min(xTime,
                         timeByDSA(xDistance, xSpeed, xAccel));
    }

    if (ball->getSpeed().getY()) {
        assert(yDistance >= 0);
        assert(ySpeed > 0);
        assert(yAccel < 0);

        yTime = std::min(yTime,
                         timeByDSA(yDistance, ySpeed, yAccel));
    }

    return std::min(xTime, yTime);
}
