#include "../utils/rect.h"

#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

class Collectible {
protected:
    float x, y;

public:
    Collectible(float startY);

    virtual void update();

    virtual void draw(float deltaTime) const = 0;

    float getX() const;
    float getY() const;
    
    Rect getBoundingBox() const {
        return Rect{ x, y, 20, 20};
    }

    virtual ~Collectible() = default;
};

#endif
