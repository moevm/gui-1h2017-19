#include "ballsutils.h"
#include "../objects/ball.h"
#include "../objects/table.h"

#include <cmath>

double BallsUtils::distance(Ball * first,
                            Ball * second)
{
    using std::sqrt;
    using std::pow;

    return sqrt(pow(first->getX() - second->getX(), 2) +
                pow(first->getY() - second->getY(), 2));
}

bool BallsUtils::collision(Ball * first,
                           Ball * second)
{
    return distance(first, second) <= first->getRadius() + second->getRadius();
}

bool BallsUtils::collisionWithTable(Ball * ball,
                                    Table * table)
{
    double ballX = ball->getX();
    double ballY = ball->getY();
    double ballRadius = ball->getRadius();

    double width = table->getWidth();
    double height = table->getHeight();

    using std::abs;

    return abs(width - ballX) <= ballRadius ||
            abs(height - ballY) <= ballRadius ||
            abs(ballX) <= ballRadius ||
            abs(ballY) <= ballRadius;
}
