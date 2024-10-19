#include "utils.h"
#include "Rect.h"
#include "../Globals.h"
#include <stdio.h>
#include <string>
#include <GL/glut.h>

void drawCircle(float x, float y, float radius, int segments) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= segments; i++) {
        float theta = 2.0f * M_PI * float(i) / float(segments);
        float dx = radius * cosf(theta);
        float dy = radius * sinf(theta);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void drawFilledCircle(float x, float y, float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * M_PI * float(i) / float(segments);
        float dx = radius * cosf(theta);
        float dy = radius * sinf(theta);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

bool checkCollision(const Rect& a, const Rect& b) {
    return (a.x < b.x + b.width &&
        a.x + a.width > b.x &&
        a.y < b.y + b.height &&
        a.y + a.height > b.y);
}
