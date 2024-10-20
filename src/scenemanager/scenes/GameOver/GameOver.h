#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "../Scene.h"
#include "../../SceneManager.h"

class GameOver : public Scene {
public:
    GameOver();

    void onSceneStart() override;
    void update(float deltaTime) override;
    void draw() override;
    void keySpecial(int key, int x, int y) override;
    void keySpecialUp(int key, int x, int y) override;
    void handleMouseClick(int button, int state, int x, int y) override;
};

#endif
