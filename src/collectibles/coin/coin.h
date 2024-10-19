#ifndef COIN_H
#define COIN_H

#include "../Collectible.h"

class Coin : public Collectible {
public:
    Coin(float startY);
    void draw(float deltaTime) const override;
};

#endif
