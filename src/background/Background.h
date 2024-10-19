#ifndef BACKGROUND_H
#define BACKGROUND_H

void drawBackground();
static void drawCloud(float x, float y, float size);
static void drawKite(float x, float y, float size);
static void drawSun(float x, float y, float radius);
static void drawGrassTriangles(float offset, float windowWidth, float floorHeight, float triangleWidth);
static void drawBushes(float offset, float windowWidth, float floorHeight, float bushWidth);
void drawLowerBoundary();
void drawUpperBoundary();

#endif
