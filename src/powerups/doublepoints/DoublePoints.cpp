#include "DoublePoints.h"
#include "../../player/Player.h"
#include "../PowerUp.h"
#include "../../Globals.h"
#include <cmath>
#include <GL/glut.h>

DoublePoints::DoublePoints(float startY)
    : PowerUp(startY) {}

void DoublePoints::draw(float deltaTime) const {
    float scale = 1.0f + 0.1f * sin(deltaTime * 2.0f);

    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // First Circle 
    glColor3f(0.0f, 1.0f, 0.0f);  // Green
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; ++i) {
        float angle = 2.0f * M_PI * i / 100;
        float radius = 20.0f;
        glVertex2f(cos(angle) * radius, sin(angle) * radius);
    }
    glEnd();

    // Second Circle
    glColor3f(0.0f, 0.8f, 1.0f);  // Blueish-green
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; ++i) {
        float angle = 2.0f * M_PI * i / 100;
        float radius = 20.0f;
        glVertex2f((30) + cos(angle) * radius, sin(angle) * radius);
    }
    glEnd();

    // Lines connecting the circles
    glColor3f(0.0f, 0.5f, 0.5f);  // Dark blue-green
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(30, 0);
    glVertex2f(-10, 20);
    glVertex2f(40, -20);
    glEnd();

    // Triangle to decorate and add more visual interest
    glColor3f(1.0f, 1.0f, 0.0f);  // Yellow
    glBegin(GL_TRIANGLES);
    glVertex2f(15, 30);
    glVertex2f(0, 0);
    glVertex2f(30, 0);
    glEnd();

    // Square around the double points
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-10, -10);
    glVertex2f(40, -10);
    glVertex2f(40, 40);
    glVertex2f(-10, 40);

    glEnd();

    glPopMatrix();
}

void DoublePoints::applyEffect(Player& player) const {
    player.isDoublePoints = true;
    player.doublePointsTimer = player.doublePointsDuration;
    audioManager.playFile("coin");
}
