#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../Globals.h"
#include "../utils/rect.h"

class Obstacle {
protected:
    float x, y;

public:
    Obstacle(float startY);

    void update();

    virtual void draw() const = 0;
    virtual Rect getBoundingBox() const = 0;

    float getX() const;
    float getY() const;

    virtual ~Obstacle() = default;
};

#endif