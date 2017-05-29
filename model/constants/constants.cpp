#include "constants.h"

namespace Constants {
static double ACCELERATION = -5.0;

void setAccel(double accel) {
    Constants::ACCELERATION = accel;
}

double getAccel() {
    return Constants::ACCELERATION;
}
}
