#ifndef INVINCIBILITY_H
#define INVINCIBILITY_H

#include "../PowerUp.h"
#include "../../utils/rect.h"

class Invincibility : public PowerUp {
public:
    Invincibility(float startY);

    void draw(float deltaTime) const override;
    void applyEffect(Player& player) const override;
};


#endif