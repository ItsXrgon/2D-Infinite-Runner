#include "Play.h"
#include "../../../player/Player.h"
#include "../../../collectibles/Collectible.h"
#include "../../../obstacles/Obstacle.h"
#include "../../../powerups/PowerUp.h"
#include "../../../background/Background.h"
#include "../../../HUD/HUD.h"
#include "../../../Globals.h"
#include "../../../Obstacles/Bird/Bird.h"
#include "../../../Obstacles/Tree/Tree.h"
#include "../../../Collectibles/Coin/Coin.h"
#include "../../../Powerups/invincibility/Invincibility.h"
#include "../../../Powerups/doublepoints/DoublePoints.h"
#include "../../../utils/Utils.h"
#include "../../../scenemanager/scenes/GameOver/GameOver.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <GL/glut.h>

float generateCooldown = 1.5f;
float timeSinceLastGeneration = 0.0f;

Player player;
std::vector<Obstacle*> obstacles;
std::vector<Collectible*> collectibles;
std::vector<PowerUp*> powerUps;

Play::Play() : Scene() {}

void Play::update(float deltaTime) {
    generateCooldown -= 0.0001;
    gameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f - 16;
    gameTime += 16.0;
    speed += 0.001;
    updateGameObjects(deltaTime);
	player.update(deltaTime);
    
	if (gameEndTime <= gameTime) {
		sceneManager.setActiveScene(new GameOver());
	}
}

void Play::onSceneStart() {
    player = Player();
    gameTime = 0;
    audioManager.playMusic("background-play");
}

void Play::draw() {
    drawBackground();
    drawHUD(player);
    player.draw();

    for (Obstacle* obstacle : obstacles) {
        obstacle->draw();
    }
    for (Collectible* collectible : collectibles) {
        collectible->draw(gameTime);
    }
    for (PowerUp* powerup : powerUps) {
        powerup->draw(gameTime);
    }
}

void Play::generateRandomObstaclesAndCollectibles() {
    const int maxObstacles = 4;
    const int maxCollectibles = 3;
    const int maxPowerUps = 2;

    int currentObstacles = obstacles.size();
    int currentCollectibles = collectibles.size();
    int currentPowerUps = powerUps.size();

    int randomChoice = rand() % 100; // Range from 0 to 99

    if (randomChoice < 50 && currentObstacles < maxObstacles) { // 50% for obstacles
        if (rand() % 2 == 0) {
            obstacles.push_back(new Bird(floorHeight + 75 + rand() % 50));
        }
        else {
            obstacles.push_back(new Tree(floorHeight));
        }
    }
    else if (randomChoice < 90 && currentCollectibles < maxCollectibles) { // 40% for collectibles
        collectibles.push_back(new Coin(floorHeight + rand() % 200));
    }
    else if (currentPowerUps < maxPowerUps) { // 10% for power-ups
        if (rand() % 2 == 0) {
            powerUps.push_back(new DoublePoints(floorHeight + rand() % 200));
        }
        else {
            powerUps.push_back(new Invincibility(floorHeight + rand() % 200));
        }
    }
}

void Play::updateGameObjects(float deltaTime) {
    timeSinceLastGeneration += deltaTime;

    if (timeSinceLastGeneration >= generateCooldown) {
        generateRandomObstaclesAndCollectibles();
        timeSinceLastGeneration = 0.0f;
    }

    // Update all obstacles
    for (size_t i = 0; i < obstacles.size(); i++) {
        if (checkCollision(player.getBoundingBox(), obstacles[i]->getBoundingBox())) {
            player.handleObjectCollision();
            if (!player.isInvincible) {
                collectibles.clear();
                obstacles.clear();
                powerUps.clear();
                player.doublePointsTimer = 0.0f;
                player.isDoublePoints = false;
                return;
            }
        }
        else if (obstacles[i]->getX() <= 0) { // Remove if off-screen
            delete obstacles[i];
            obstacles.erase(obstacles.begin() + i);
        }
        obstacles[i]->update();
    }

    // Update all collectibles
    for (size_t i = 0; i < collectibles.size(); i++) {
        collectibles[i]->update();
        if (checkCollision(player.getBoundingBox(), collectibles[i]->getBoundingBox())) {
            player.handleCollectibleCollision();
            delete collectibles[i];
            collectibles.erase(collectibles.begin() + i);
        }
        else if (collectibles[i]->getX() <= 0) { // Remove if off-screen
            delete collectibles[i];
            collectibles.erase(collectibles.begin() + i);
        }
    }

    // Update all powerups
    for (size_t i = 0; i < powerUps.size(); i++) {
        powerUps[i]->update();
        if (checkCollision(player.getBoundingBox(), powerUps[i]->getBoundingBox())) {
            powerUps[i]->applyEffect(player);
            delete powerUps[i];
            powerUps.erase(powerUps.begin() + i);
        }
        else if (powerUps[i]->getX() <= 0) { // Remove if off-screen
            delete powerUps[i];
            powerUps.erase(powerUps.begin() + i);
        }
    }
}

void Play::keySpecial(int key, int x, int y) {
    if (key == GLUT_KEY_DOWN) {
        if (player.isGrounded) {
            player.duck();
        }
        else if (!player.isJumping) {
            player.y -= 10;
        }
    }

    if (key == GLUT_KEY_UP && player.isGrounded) {
        player.jump();
        player.unDuck();
    }
}


void Play::keySpecialUp(int key, int x, int y) {
    if (key == GLUT_KEY_DOWN) {
        player.unDuck();
    }
}

void Play::handleMouseClick(int button, int state, int x, int y) {}