#include "../utils/Utils.h"
#include "../Globals.h"
#include "Background.h"
#include <stdio.h>
#include <string>
#include <GL/glut.h>

float lowerOffset = 0.0f;
int cloudOffset = 0.0f;

static void drawCloud(float x, float y, float size) {
    glColor3f(0.8f, 0.8f, 0.8f);
    drawFilledCircle(x, y, size, 100);
    drawFilledCircle(x - size / 1.5, y, size / 1.5, 100);
    drawFilledCircle(x + size / 1.5, y, size / 1.5, 100);
    drawFilledCircle(x - size / 3.0, y + size / 2.0, size / 1.8, 100);
    drawFilledCircle(x + size / 3.0, y + size / 2.0, size / 1.8, 100);
}

static void drawSun(float x, float y, float radius) {
    glColor3ub(253, 184, 19);
    drawFilledCircle(x, y, radius, 100);

    glColor3ub(253, 184, 19);
    glBegin(GL_LINES);
    for (int i = 0; i < 360; i += 30) {
        float angle = i * (M_PI / 180.0f);
        float rayX = radius * cosf(angle);
        float rayY = radius * sinf(angle);
        glVertex2f(x, y);
        glVertex2f(x + rayX * 1.5f, y + rayY * 1.5f);
    }
    glEnd();
}

static void drawKite(float x, float y, float size) {
    glColor3ub(255, 0, 0);

    glBegin(GL_TRIANGLES);
    glVertex2f(x, y + size);
    glVertex2f(x - size, y);
    glVertex2f(x + size, y);

    glVertex2f(x, y - size);
    glVertex2f(x - size, y);
    glVertex2f(x + size, y);
    glEnd();

    glColor3ub(0, 0, 0);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(x, y - size);
    glVertex2f(x - size / 4.0f, y - size * 1.5f);

    glVertex2f(x - size / 4.0f, y - size * 1.5f);
    glVertex2f(x + size / 4.0f, y - size * 2.0f);

    glVertex2f(x + size / 4.0f, y - size * 2.0f);
    glVertex2f(x, y - size * 2.5f);
    glEnd();
}

static void drawGrassTriangles(float offset, float windowWidth, float floorHeight, float triangleWidth) {
    float const triangleHeight = floorHeight / 4.0;

    for (float i = offset; i < windowWidth; i += triangleWidth) {
        glBegin(GL_TRIANGLES);
        glColor3ub(19, 109, 21);
        glVertex3f(i, floorHeight, 0.0f);
        glVertex3f(i + (triangleWidth / 2.0), floorHeight - triangleHeight, 0.0f);
        glVertex3f(i + triangleWidth, floorHeight, 0.0f);
        glEnd();
    }

    for (float i = offset - triangleWidth / 2; i < windowWidth; i += triangleWidth) {
        glBegin(GL_TRIANGLES);
        glColor3ub(17, 124, 19);
        glVertex3f(i, floorHeight, 0.0f);
        glVertex3f(i + (triangleWidth / 2.0), floorHeight - triangleHeight, 0.0f);
        glVertex3f(i + triangleWidth, floorHeight, 0.0f);
        glEnd();
    }
}

static void drawBushes(float offset, float windowWidth, float floorHeight, float bushWidth) {
    glColor3ub(19, 200, 21);
    for (float i = offset; i < windowWidth; i += bushWidth) {
        glBegin(GL_POLYGON);
        for (int j = 0; j < 51; j++) {
            float theta = 2.0f * M_PI * float(j) / float(100);
            float x = bushWidth / 3 * cosf(theta);
            float y = bushWidth / 3 * sinf(theta);
            glVertex2f(x + i, y + floorHeight);
        }
        glEnd();
    }
}

void drawLowerBoundary() {

    glBegin(GL_POLYGON);
    glColor3ub(107, 84, 40);
    glVertex2f(0, floorHeight);
    glVertex2f(windowWidth, floorHeight);
    glColor3ub(64, 41, 5);
    glVertex2f(windowWidth, 0);
    glVertex2f(0, 0);
    glEnd();



    float const triangleCount = 15.0;
    float const triangleWidth = windowWidth / triangleCount;
    float const bushCount = 10;
    float const bushWidth = 15;
    
    // Floor parallax
    lowerOffset -= speed;
    if (lowerOffset <= -triangleWidth) {
        lowerOffset = 0.0f;
    }

    drawBushes(lowerOffset, windowWidth, floorHeight, bushWidth);
    drawGrassTriangles(lowerOffset, windowWidth, floorHeight, triangleWidth);

    glColor3ub(68, 187, 255);
    glBegin(GL_QUADS);
    glVertex2f(0, 20);
    glVertex2f(windowWidth, 20);
    glVertex2f(windowWidth, 0);
    glVertex2f(0, 0);
    glEnd();
}

void drawUpperBoundary() {

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);

    // Cloud parallax
    cloudOffset += speed;
    if (cloudOffset >= windowWidth) {
        cloudOffset = 0;
    }

    drawCloud((0 - cloudOffset + windowWidth) % windowWidth, 500, 50);   // Cloud 1
    drawCloud((400 - cloudOffset + windowWidth) % windowWidth, 470, 70);   // Cloud 2
    drawCloud((800 - cloudOffset + windowWidth) % windowWidth, 450, 60);   // Cloud 3
    drawCloud((1200 - cloudOffset + windowWidth) % windowWidth, 490, 60);  // Cloud 4
    drawCloud((1600 - cloudOffset + windowWidth) % windowWidth, 420, 55);  // Cloud 5
    drawKite(500, 400, 40);
    drawSun(25, windowHeight, 75);
}

void drawBackground() {
    drawLowerBoundary();
    drawUpperBoundary();
}