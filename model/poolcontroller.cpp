#include "poolcontroller.h"
#include "objects/table.h"
#include "objects/snapshot.h"
#include "constants/constants.h"

#include <limits>
#include <algorithm>

double PoolController::timeToStop() const
{
    return table->shortestTimeToStop();
}

double PoolController::timeToWallCollision() const
{
    return table->shortestTimeToWall();
}

void PoolController::setTable(Table * table)
{
    this->table = table;
}

void PoolController::calculateHit()
{
    using Constants::GameStatus;

    while (table->hasMoving()) {
        double timeToNextStep = timeToStop();
        GameStatus status = GameStatus::BALL_STOPPED;

        double timeToWall = timeToWallCollision();
        if (timeToWall < timeToNextStep) {
            timeToNextStep = timeToWall;
            status = GameStatus::WALL_COLLISION;
        }

        // TODO: для каждой пары шаров найти время до столкновения (если
        // столкнутся)
        // TODO: переместить шары ко времени близжайшего события
        // TODO: пересчитать параметры шаров и исключить остановившиеся
    }
}

PoolController::~PoolController()
{
    std::for_each(history.begin(),
                  history.end(),
                  [](Snapshot * snapshot) {
        delete snapshot;
    });

    delete table;
}
