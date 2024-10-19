#include "Collectible.h"
#include "../Globals.h"

Collectible::Collectible(float startY)
    : x(windowWidth + 0.0f), y(startY) {}

void Collectible::update() {
    x -= speed;  // Move collectible to the left
}

float Collectible::getX() const {
    return x;
}

float Collectible::getY() const {
    return y;
}
