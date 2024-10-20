#include "Menu.h"
#include "../../../utils/Button.h"
#include "../../SceneManager.h"
#include "../../scenes/Play/Play.h"
#include "../../../Globals.h"
#include <string>
#include <GL/glut.h>

Menu::Menu() : Scene() {
	this->playButton = Button("Play", (windowWidth * 0.46f), windowHeight * 0.57f, 100, 50);
	this->exitButton = Button("Exit", (windowWidth * 0.46f), windowHeight * 0.42f, 100, 50);
}

void Menu::onSceneStart() {
}

void Menu::draw() {
	playButton.draw();
	exitButton.draw();
}


void Menu::handleMouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (playButton.isClicked(x, y)) {
			sceneManager.setActiveScene(new Play());
		}
	}
}

void Menu::update(float deltaTime) {
}

void Menu::keySpecial(int key, int x, int y) {
}


void Menu::keySpecialUp(int key, int x, int y) {
}