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
                        accel * std::pow(timeToStop, 2);

    if (distToStop < dist) {
        return std::numeric_limits<double>::infinity();
    }

    double discriminant = std::pow(speed, 2) + 4 * accel * dist;
    assert(discriminant >= 0);

    using std::min;
    using std::sqrt;
    double time = min((-speed - sqrt(discriminant)) / (2 * accel),
                      (-speed + sqrt(discriminant)) / (2 * accel));
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

    return abs(width - ballX) <= ballRadius ||
            abs(height - ballY) <= ballRadius ||
            abs(ballX) <= ballRadius ||
            abs(ballY) <= ballRadius;
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
        xDistance = table->getWidth() - ball->getPosition().getX();
        xSpeed = ball->getSpeed().getX();
        xAccel = ball->getAccel().getX();
    } else {
        xDistance = ball->getPosition().getX();
        xSpeed = -ball->getSpeed().getX();
        xAccel = -ball->getAccel().getX();
    }

    if (ball->getSpeed().getY() > 0) {
        yDistance = table->getHeight() - ball->getPosition().getY();
        ySpeed = ball->getSpeed().getY();
        yAccel = ball->getAccel().getY();
    } else {
        yDistance = ball->getPosition().getY();
        ySpeed = -ball->getSpeed().getY();
        yAccel = -ball->getAccel().getY();
    }

    assert(xDistance >= 0);
    assert(xSpeed > 0);
    assert(xAccel < 0);

    assert(yDistance >= 0);
    assert(ySpeed > 0);
    assert(yAccel < 0);

    return std::min(timeByDSA(xDistance, xSpeed, xAccel),
                    timeByDSA(yDistance, ySpeed, yAccel));
}
