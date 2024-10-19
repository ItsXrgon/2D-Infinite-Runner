#include "Obstacle.h"
#include "../Globals.h"

Obstacle::Obstacle(float startY)
    : x(windowWidth + 0.0f), y(startY) {}

void Obstacle::update() {
    x -= speed; 
}

float Obstacle::getX() const {
    return x;
}

float Obstacle::getY() const {
    return y;
}
