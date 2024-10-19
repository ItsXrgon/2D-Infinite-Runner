#ifndef POWERUP_H
#define POWERUP_H

#include "../utils/rect.h"
#include "../Globals.h"

class PowerUp {
protected:
    float x, y;

public:
    PowerUp(float startY);

    virtual void applyEffect(class Player& player) const = 0;
    virtual void draw(float deltaTime) const = 0;
    void update();


    float getX() const;
    float getY() const;

    virtual ~PowerUp() = default;
    Rect getBoundingBox() const {
        return Rect{ x, y, 20, 20 };
    }
};

#endif