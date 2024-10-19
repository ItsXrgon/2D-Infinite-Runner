#include "../utils/rect.h"

#pragma once
class Player {
public:
    float x, y;
    int health, maxHealth;
    float width, height;
    bool isJumping, isDucking, isGrounded, isColliding;
    bool isInvincible;
    float invincibilityDuration;
    float invincibilityTimer;
    bool isDoublePoints;
    float doublePointsDuration;
    float doublePointsTimer;

    Player();
    void draw();
    void update(float deltaTime);  
    void jump();
    void duck();
    void unDuck();
    void handleObjectCollision();
    void handleCollectibleCollision();

    Rect getBoundingBox();
};

