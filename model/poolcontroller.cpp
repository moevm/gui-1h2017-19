#include "poolcontroller.h"
#include "objects/table.h"

#include <limits>

double PoolController::timeToStop() const
{
    return table->shortestTimeToStop();
}

PoolController::PoolController()
{
}

void PoolController::calculateHit()
{
    while (table->hasMoving()) {
        double timeToNextStep = timeToStop();
        Status status = BALL_STOPPED;

        // TODO: для каждого шара найти, через сколько он столкнется со стеной
        // TODO: для каждой пары шаров найти время до столкновения (если
        // столкнутся)
        // TODO: переместить шары ко времени близжайшего события
        // TODO: пересчитать параметры шаров и исключить остановившиеся
    }
}
