#include "GameOver.h"
#include "../../../Globals.h"
#include <string>
#include <GL/glut.h>

GameOver::GameOver() : Scene() {}

void GameOver::onSceneStart() {
    audioManager.stopMusic();
    if (gameTime >= gameEndTime) {
        audioManager.playMusic("background-win");
    } else {
		audioManager.playMusic("background-gameover");
    }
}

void GameOver::draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    std::string message = gameTime >= gameEndTime ? "You Win!" : "Game Over!";
    std::string scoreMessage = "Score: " + std::to_string(score);

    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2f(windowWidth / 2, windowHeight / 2);
    for (const char& letter : message) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, letter);
    }

    glRasterPos2f(windowWidth / 2, windowHeight / 2 - 100);
	for (const char& letter : scoreMessage) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, letter);
	}

    glutSwapBuffers();
}

void GameOver::update(float deltaTime) { }

void GameOver::keySpecial(int key, int x, int y) { }


void GameOver::keySpecialUp(int key, int x, int y) { }


void GameOver::handleMouseClick(int button, int state, int x, int y) {}