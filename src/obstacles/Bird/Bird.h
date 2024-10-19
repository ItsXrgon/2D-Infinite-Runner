#ifndef BIRDOBSTACLE_H
#define BIRDOBSTACLE_H

#include "../Obstacle.h"
#include "../../utils/rect.h"

class Bird : public Obstacle {
public:
    mutable float wingAnimCounter;
    mutable bool wingUp;
    Bird(float startY);

    void draw() const override;
    Rect getBoundingBox() const override;
};

#endif