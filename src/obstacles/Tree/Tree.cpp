#include "Tree.h"
#include <GL/glut.h>

Tree::Tree(float startY)
    : Obstacle(startY) {}

void Tree::draw() const {
    float const trunkWidth = 10;
    float const trunkHeight = 10;
    float const leafSize = 20;

    // trunk
    glColor3f(0.4f, 0.26f, 0.13f);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + trunkWidth, y);
    glVertex2f(x + trunkWidth, y + trunkHeight);
    glVertex2f(x, y + trunkHeight);
    glEnd();

    // leaves
    glColor3f(0.0f, 0.5f, 0.0f);
    glBegin(GL_TRIANGLES);

    // Bottom layer of leaves 
    glVertex2f(x - leafSize, y + trunkHeight);
    glVertex2f(x + trunkWidth + leafSize, y + trunkHeight);
    glVertex2f(x + trunkWidth / 2.0f, y + trunkHeight + leafSize);

    // Middle layer of leaves
    glVertex2f(x - leafSize * 0.8f, y + trunkHeight + leafSize * 0.5f);
    glVertex2f(x + trunkWidth + leafSize * 0.8f, y + trunkHeight + leafSize * 0.5f);
    glVertex2f(x + trunkWidth / 2.0f, y + trunkHeight + leafSize * 1.5f);

    // Top layer of leaves
    glVertex2f(x - leafSize * 0.6f, y + trunkHeight + leafSize);
    glVertex2f(x + trunkWidth + leafSize * 0.6f, y + trunkHeight + leafSize);
    glVertex2f(x + trunkWidth / 2.0f, y + trunkHeight + leafSize * 2.0f);

    glEnd();
}

Rect Tree::getBoundingBox() const {
    return Rect{ x, y, 30, 40 };
}