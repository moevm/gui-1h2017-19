#include "constants.h"

namespace Constants {
static double ACCELERATION = -2.5;

void setAccel(double accel) {
    Constants::ACCELERATION = accel;
}

double getAccel() {
    return Constants::ACCELERATION;
}
}
