#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "scenes/Scene.h"

class SceneManager {
protected:
	Scene* activeScene;
public:
    SceneManager();

    void setActiveScene(Scene* scene);
    void update(float deltaTime);
    void draw();
	void keySpecial(int key, int x, int y);
	void keySpecialUp(int key, int x, int y);
    void handleMouseClick(int button, int state, int x, int y);
};

#endif
