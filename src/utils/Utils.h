#ifndef UTILS_H
#define UTILS_H

#include "Rect.h"

void drawCircle(float cx, float cy, float radius, int segments);
void drawFilledCircle(float x, float y, float radius, int segments);
bool checkCollision(const Rect& a, const Rect& b);

#endif
