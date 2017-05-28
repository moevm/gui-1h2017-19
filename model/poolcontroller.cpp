#include "poolcontroller.h"
#include "objects/table.h"
#include "objects/snapshot.h"
#include "constants/constants.h"
#include "objects/ball.h"

#include <limits>
#include <algorithm>
#include <QDebug>

using Constants::GameStatus;

std::vector<Snapshot *> PoolController::getHistory() const
{
    return history;
}

double PoolController::timeToStop() const
{
    return table->shortestTimeToStop();
}

double PoolController::timeToWallCollision() const
{
    return table->shortestTimeToWall();
}

void PoolController::saveToHistory(double calculationTime, GameStatus status)
{
    std::string statusName;
    switch (status) {
    case GameStatus::BALL_STOPPED:
        statusName = "Остановка шара";
        break;
    case GameStatus::WALL_COLLISION:
        statusName = "Столкновение со стеной";
        break;
    case GameStatus::BALLS_COLLISION:
        statusName = "Соударение шаров";
        break;
    default:
        statusName = "Неизвестный статус";
        break;
    }
    history.push_back(new Snapshot(statusName,
                                   table,
                                   calculationTime));
}

void PoolController::setTable(Table * table)
{
    if (this->table != nullptr) {
        delete this->table;
    }
    this->table = table;
}

void PoolController::calculateHit()
{
    double calculationTime = 0;

    history.clear();
    history.push_back(new Snapshot("start",
                                   table,
                                   calculationTime));

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

        table->goToNextStep(timeToNextStep);

        // TODO: пересчитать параметры шаров после соударения
        table->recalculateWallCollision();

        calculationTime += timeToNextStep;
        saveToHistory(calculationTime, status);
    }

    qDebug() << "Рассчет завершен";
}

bool PoolController::addBall(Ball * ball)
{
    return table->addBall(ball);
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
