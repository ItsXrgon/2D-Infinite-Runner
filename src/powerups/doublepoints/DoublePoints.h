#ifndef DOUBLEPOINTS_H
#define INVINCIBILITY_H

#include "../PowerUp.h"
#include "../../utils/rect.h"

class DoublePoints : public PowerUp {
public:
    DoublePoints(float startY);

    void draw(float deltaTime) const override;
    void applyEffect(Player& player) const override;
};


#endif