#include "SceneManager.h"
#include "scenes/Menu/Menu.h"
#include "scenes/Play/Play.h"
#include "scenes/GameOver/GameOver.h"

SceneManager::SceneManager() {
	activeScene = nullptr;
}

void SceneManager::setActiveScene(Scene* scene) {
    activeScene = scene;
	scene->onSceneStart();
}

void SceneManager::update(float deltaTime) {
	activeScene->update(deltaTime);
}

void SceneManager::draw() {
	activeScene->draw();
}


void SceneManager::keySpecial(int key, int x, int y) {
	activeScene->keySpecial(key, x, y);
}

void SceneManager::keySpecialUp(int key, int x, int y) {
	activeScene->keySpecialUp(key, x, y);
}


void SceneManager::handleMouseClick(int button, int state, int x, int y) {
	activeScene->handleMouseClick(button, state, x, y);
}