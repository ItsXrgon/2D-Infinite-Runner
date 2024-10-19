#include "Bird.h"
#include <cmath>
#include <GL/glut.h>

Bird::Bird(float startY)
    : Obstacle(startY) {
    wingAnimCounter = 0;
    wingUp = false;
}

void Bird::draw() const {
    float const bodyWidth = 40.0f;
    float const bodyHeight = 20.0f;
    float const beakSize = 10.0f;
    float const wingWidth = 15.0f;
    float const wingHeight = 10.0f;
    float const wingOffset = wingUp ? 20 : 0;

    // Body
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(x + beakSize, y);
    glVertex2f(x + beakSize + bodyWidth, y);
    glVertex2f(x + beakSize + bodyWidth, y + bodyHeight);
    glVertex2f(x + beakSize, y + bodyHeight);
    glEnd();

    // Beak
    glColor3f(1.0f, 0.6f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(x + beakSize, y + bodyHeight * 0.4f);
    glVertex2f(x + beakSize, y + bodyHeight * 0.6f);
    glVertex2f(x, y + bodyHeight * 0.5f);
    glEnd();

    // Wing
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex2f(x + beakSize + bodyWidth * 0.3f, y + bodyHeight * 0.5f);
    glVertex2f(x + beakSize + bodyWidth + wingWidth - wingOffset, y + bodyHeight * 0.85f + wingOffset);
    glVertex2f(x + beakSize + bodyWidth + wingWidth, y + bodyHeight * 0.15f + wingOffset);
    glEnd();

    wingAnimCounter += 0.1;
    if (wingAnimCounter >= 2.0) {
        wingUp = !wingUp;
        wingAnimCounter = 0;
    }
}

Rect Bird::getBoundingBox() const {
    return Rect{ x, y, 40, 20 };
}
