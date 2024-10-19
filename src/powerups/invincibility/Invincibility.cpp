#include "Invincibility.h"
#include "../../player/Player.h"
#include "../PowerUp.h"
#include "../../Globals.h"
#include <cmath>
#include <GL/glut.h>

Invincibility::Invincibility(float startY)
    : PowerUp(startY) {}

void Invincibility::draw(float deltaTime) const {
    float rotationAngle = deltaTime * 100.0f;

    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);

    // Circle
    glColor3f(1.0f, 1.0f, 0.0f);  // Yellow
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; ++i) {
        float angle = 2.0f * M_PI * i / 100;
        float radius = 25.0f;
        glVertex2f(cos(angle) * radius, sin(angle) * radius);
    }
    glEnd();

    // Star
    glColor3f(1.0f, 0.8f, 0.0f);  // Gold
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 0); 
    for (int i = 0; i <= 10; ++i) {
        float angle = i * 2.0f * M_PI / 5.0f; 
        float radius = (i % 2 == 0) ? 15.0f : 30.0f;
        glVertex2f(cos(angle) * radius, sin(angle) * radius);
    }
    glEnd();

    // Rays of light
    glColor3f(1.0f, 1.0f, 0.0f);  // Yellow
    glBegin(GL_LINES);
    for (int i = 0; i < 8; ++i) {
        float angle = i * M_PI / 4.0f;
        glVertex2f(cos(angle) * 30.0f, sin(angle) * 30.0f);
        glVertex2f(cos(angle) * 40.0f, sin(angle) * 40.0f);
    }
    glEnd();

    // Inner circle
    glColor3f(1.0f, 0.6f, 0.0f);  // Orange
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; ++i) {
        float angle = 2.0f * M_PI * i / 100;
        float radius = 10.0f;
        glVertex2f(cos(angle) * radius, sin(angle) * radius);
    }
    glEnd();

    glPopMatrix();
}

void Invincibility::applyEffect(Player& player) const {
    player.isInvincible = true;
    player.invincibilityTimer = player.invincibilityDuration; 
}
