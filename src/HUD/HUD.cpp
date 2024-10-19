#include "../utils/Utils.h"
#include "../Globals.h"
#include "../player/Player.h"
#include "HUD.h"
#include <string>
#include <GL/glut.h>

void displayNumber(std::string text, float x, float y)
{
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2f(x, y);
    for (int i = 0; i < text.size(); ++i)
    {
        char c = text[i];
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void drawHUD(Player& player) {
	for (int i = 0; i < player.maxHealth; i++) {
		if (i < player.health) {
			glBegin(GL_TRIANGLE_FAN);
		}
		else {
			glBegin(GL_LINE_LOOP);
		}
		for (float angle = 0; angle < 2 * M_PI; angle += 0.01) {
			float x = 16 * pow(sin(angle), 3);
			float y = 13 * cos(angle) - 5 * cos(2 * angle) - 2 * cos(3 * angle) - cos(4 * angle);

			glVertex2f(x + windowWidth - 220 - (40 * i), y + (windowHeight - 25));
		}
		glEnd();
	}
	// Timer
	displayNumber(std::to_string(int(gameTime)), windowWidth - 50, windowHeight - 25);

	// Score
	displayNumber(std::to_string(score), windowWidth - 150, windowHeight - 25);
	// Score Coin 
    glPushMatrix();
    glTranslatef(windowWidth - 110, windowHeight - 20, 0.0f);

    // Circle 1
    glColor3f(1.0f, 0.84f, 0.0f); // Golden-yellow color for the coin
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 100; i++) {
        float theta = 2.0f * M_PI * float(i) / float(100);
        float circleX = 15 * cosf(theta);
        float circleY = 15 * sinf(theta);
        glVertex2f(circleX, circleY);
    }
    glEnd();

    // Circle 2
    glColor3f(1.0f, 0.9f, 0.5f); // Ligher gold
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 100; i++) {
        float theta = 2.0f * M_PI * float(i) / float(100);
        float circleX = 10 * cosf(theta);
        float circleY = 10 * sinf(theta);
        glVertex2f(circleX, circleY);
    }
    glEnd();

    // Line engraving
    glColor3f(0.8f, 0.7f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(-5, -2.5);
    glVertex2f(5, -2.5);
    glEnd();

    // Triangle
    glColor3f(0.9f, 0.8f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-5, 2.5);
    glVertex2f(0, 7.5);
    glVertex2f(5, 2.5);
    glEnd();

    glPopMatrix();

    if (player.isInvincible) {
        displayNumber("Duration Invincible: " + std::to_string(int(player.invincibilityTimer)), 150, windowHeight - 25);
    }
        
    if (player.isDoublePoints) {
        displayNumber("2x Points Duration: " + std::to_string(int(player.doublePointsTimer)), 350, windowHeight - 25);
    }
}