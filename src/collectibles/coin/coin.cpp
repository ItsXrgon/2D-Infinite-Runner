#include "Coin.h"
#include "../../Globals.h"
#include <cmath>
#include <GL/glut.h>

Coin::Coin(float startY)
    : Collectible(startY) {}

void Coin::draw(float deltaTime) const {
    float bobbing = 5.0f * sin(deltaTime * 4.0f);

    glPushMatrix();
    glTranslatef(x, y + bobbing, 0.0f);

    // Circle 1
    glColor3f(1.0f, 0.84f, 0.0f); // Golden-yellow color for the coin
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 100; i++) {
        float theta = 2.0f * M_PI * float(i) / float(100);
        float circleX = 20 * cosf(theta);
        float circleY = 20 * sinf(theta);
        glVertex2f(circleX, circleY);
    }
    glEnd();

    // Circle 2
    glColor3f(1.0f, 0.9f, 0.5f); // Ligher gold
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 100; i++) {
        float theta = 2.0f * M_PI * float(i) / float(100);
        float circleX = 15 * cosf(theta);
        float circleY = 15 * sinf(theta);
        glVertex2f(circleX, circleY);
    }
    glEnd();

    // Line engraving
    glColor3f(0.8f, 0.7f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(-10, 0);
    glVertex2f(10, 0);
    glEnd();

    // Triangle
    glColor3f(0.9f, 0.8f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-5, 5);
    glVertex2f(0, 10);
    glVertex2f(5, 5);
    glEnd();

    glPopMatrix();
}
