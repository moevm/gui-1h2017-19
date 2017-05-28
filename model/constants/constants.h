#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants {
enum GameStatus {
    BALL_STOPPED,
    WALL_COLLISION,
    BALLS_COLLISION
};

double getAccel();
void setAccel(double accel);
}

#endif // CONSTANTS_H
