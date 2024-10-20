#ifndef MENU_H
#define MENU_H

#include "../Scene.h"
#include "../../SceneManager.h"
#include "../../../utils/button.h"

class Menu : public Scene {
protected:
    Button playButton;
    Button exitButton;
public:
    Menu();

    void onSceneStart() override;
    void update(float deltaTime) override;
    void draw() override;
    void keySpecial(int key, int x, int y) override;
    void keySpecialUp(int key, int x, int y) override;
    void handleMouseClick(int button, int state, int x, int y) override;
};

#endif
