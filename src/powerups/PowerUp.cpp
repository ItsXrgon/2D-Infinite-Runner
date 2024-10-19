#include "Powerup.h"
#include "../Globals.h"

PowerUp::PowerUp(float startY)
    : x(windowWidth + 50.0f), y(startY) {}

void PowerUp::update() {
    x -= speed;
}

float PowerUp::getX() const {
    return x;
}

float PowerUp::getY() const {
    return y;
}
