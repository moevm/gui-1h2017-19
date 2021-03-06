#include "ballsutils.h"
#include "../objects/ball.h"
#include "../objects/table.h"

#include <cmath>
#include <limits>
#include <algorithm>
#include <cassert>
#include <QDebug>

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

double BallsUtils::distance(const Ball * first,
                            const Ball * second)
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
    const double dist = distance(first, second);
    const double mindist = first->getRadius() + second->getRadius();
    return dist <= mindist;
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

double BallsUtils::timeToCollision(const Ball * first, const Ball * second)
{
    double time = prefferedStepTime(first, second);
    if (time == std::numeric_limits<double>::infinity()) {
        return time;
    }

    Ball copy1(*first);
    Ball copy2(*second);

    const double mindist = first->getRadius() + second->getRadius();

    time = 0;
    while (distance(&copy1, &copy2) >= mindist) {
        double timeDiff = prefferedStepTime(&copy1, &copy2);
        if (timeDiff == std::numeric_limits<double>::infinity()) {
            return timeDiff;
        }
        copy1.goToNextStep(timeDiff);
        copy2.goToNextStep(timeDiff);
        time += timeDiff;
        qDebug() << "Dist&time" << distance(&copy1, &copy2) << " " << time;
    }

    return time;
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

double BallsUtils::prefferedStepTime(const Ball * first, const Ball * second)
{
    DoubleVector2D f2sVec;
    f2sVec.setX(second->getPosition().getX() - first->getPosition().getX());
    f2sVec.setY(second->getPosition().getY() - first->getPosition().getY());

    DoubleVector2D s2fVec;
    s2fVec.setX(first->getPosition().getX() - second->getPosition().getX());
    s2fVec.setY(first->getPosition().getY() - second->getPosition().getY());

    double firstProj = first->getSpeed().getX() * f2sVec.getX() +
                       first->getSpeed().getY() * f2sVec.getY();
    if (f2sVec.getSize() > 0) {
        firstProj /= f2sVec.getSize();
    } else {
        firstProj = 0;
    }

    double secondProj = second->getSpeed().getX() * s2fVec.getX() +
                        second->getSpeed().getY() * s2fVec.getY();
    if (s2fVec.getSize() > 0) {
        secondProj /= s2fVec.getSize();
    } else {
        secondProj = 0;
    }

    const double speedProj = firstProj + secondProj;
    const double dist = distance(first, second) -
                        (first->getRadius() + second->getRadius());

    if (speedProj <= 1e-32) {
        return std::numeric_limits<double>::infinity();
    }

    qDebug() << "dist&speed" << dist << " " << speedProj;
    assert(dist != std::numeric_limits<double>::infinity());
    return std::max(0.0001,
                    dist / speedProj);
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
        xTime = std::min(xTime,
                         timeByDSA(xDistance, xSpeed, xAccel));
    }

    if (ball->getSpeed().getY()) {
        yTime = std::min(yTime,
                         timeByDSA(yDistance, ySpeed, yAccel));
    }

    return std::min(xTime, yTime);
}

void BallsUtils::recalculateCollision(Ball * first, Ball * second)
{
    // меняем систему отсчета (2-ой шар)
    const double secondXSpeed = second->getSpeed().getX();
    const double secondYSpeed = second->getSpeed().getY();

    DoubleVector2D speed;

    speed = first->getSpeed();
    speed.setX(speed.getX() - secondXSpeed);
    speed.setY(speed.getY() - secondYSpeed);
    first->setSpeed(speed);

    speed = second->getSpeed();
    speed.setX(speed.getX() - secondXSpeed);
    speed.setY(speed.getY() - secondYSpeed);
    second->setSpeed(speed);

    // считаем скорости
    // считаем вектор first.center -> second.center
    DoubleVector2D vec;
    double xvec = second->getPosition().getX() - first->getPosition().getX();
    double yvec = second->getPosition().getY() - first->getPosition().getY();
    vec.setX(xvec);
    vec.setY(yvec);

    // ищем косинус угла между first.speed (в новой системе отсчета) и
    // vec
    double xspeed = first->getSpeed().getX();
    double yspeed = first->getSpeed().getY();
    double cosangle = (xspeed * xvec + yspeed * yvec) /
                      (first->getSpeed().getSize() * vec.getSize());

    // укорачиваем вектор vec до проекции first.speed на него
    vec.setSize(first->getSpeed().getSize() * cosangle);
    xvec = vec.getX();
    yvec = vec.getY();

    // ищем новый вектор first.speed с помощью вычитания векторов first.speed
    // и vec
    xspeed -= xvec;
    yspeed -= yvec;

    // устанавливаем новые вектора скоростей и возвращаем систему отсчета
    speed.setX(xspeed + secondXSpeed);
    speed.setY(yspeed + secondYSpeed);
    first->setSpeed(speed);

    speed.setX(xvec + secondXSpeed);
    speed.setY(yvec + secondYSpeed);
    second->setSpeed(speed);
}
