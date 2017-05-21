#include "ballsutils.h"
#include "../objects/ball.h"
#include "../objects/table.h"

#include <cmath>

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
