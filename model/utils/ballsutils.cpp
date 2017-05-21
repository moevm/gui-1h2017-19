#include "ballsutils.h"
#include "../objects/ball.h"

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
