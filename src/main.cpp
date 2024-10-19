#include "player/Player.h"
#include "obstacles/Obstacle.h"
#include "collectibles/Collectible.h"
#include "powerups/PowerUp.h"
#include "background/Background.h"
#include "HUD/HUD.h"
#include "utils/Utils.h"
#include "Globals.h"
#include "Obstacles/Bird/Bird.h"
#include "Obstacles/Tree/Tree.h"
#include "Collectibles/Coin/Coin.h"
#include "Powerups/invincibility/Invincibility.h"
#include "Powerups/doublepoints/DoublePoints.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <GL/glut.h>

int windowWidth = 1000;
int windowHeight = 600;
int floorHeight = 200; 
float speed = 1.5f; 
float gameTime = 0.0;
int score = 0;
int lastTime = glutGet(GLUT_ELAPSED_TIME);
float deltaTime = 0;
float generateCooldown = 1.5f;
float timeSinceLastGeneration = 0.0f;

void generateRandomObstaclesAndCollectibles(float playerX);
void updateGameObjects(float deltaTime);
void calculateDeltaTime();
void keySpecial(int key, int x, int y);
void keySpecialUp(int key, int x, int y);

// Game state
Player player;
std::vector<Obstacle*> obstacles;
std::vector<Collectible*> collectibles;
std::vector<PowerUp*> powerUps;

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    gameTime = 0;
    player = Player();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawBackground();
    drawHUD(player);
    player.draw();

    calculateDeltaTime(); // Calculate the time since the last frame
    gameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f - 16;
    updateGameObjects(deltaTime);

    for (Obstacle* obstacle : obstacles) {
        obstacle->draw();
    }
    for (Collectible* collectible : collectibles) {
        collectible->draw(gameTime);
    }
    for (PowerUp* powerup : powerUps) {
        powerup->draw(gameTime);
    }
    glFlush();
}

void update(int value) {
    player.update(deltaTime);

    glutPostRedisplay();
    gameTime += 16.0;
    speed += 0.001;
    generateCooldown -= 0.0001;
    glutTimerFunc(16, update, 0);  // ~16ms (~60fps)
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Runner Game");

    init();

    glutDisplayFunc(display);
    glutSpecialFunc(keySpecial);
    glutSpecialUpFunc(keySpecialUp);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}

void generateRandomObstaclesAndCollectibles(float playerX) {
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

void updateGameObjects(float deltaTime) {
    timeSinceLastGeneration += deltaTime;

    if (timeSinceLastGeneration >= generateCooldown) {
        generateRandomObstaclesAndCollectibles(player.x);
        timeSinceLastGeneration = 0.0f;
    }

    bool colliding = false;
    // Update all obstacles
    for (size_t i = 0; i < obstacles.size(); i++) {
        obstacles[i]->update();
        if (checkCollision(player.getBoundingBox(), obstacles[i]->getBoundingBox())) {
            colliding = true;
            player.handleObjectCollision(); 
        }
        else if (obstacles[i]->getX() <= 0) { // Remove if off-screen
            delete obstacles[i];
            obstacles.erase(obstacles.begin() + i);
        }
        player.isColliding = colliding;
    }

    // Update all collectibles
    for (size_t i = 0; i < collectibles.size();  i++) {
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

void keySpecial(int key, int x, int y) {
    if (key == GLUT_KEY_DOWN) {
        if (player.isGrounded) {
            player.duck();
        }
        else if(!player.isJumping) {
            player.y -= 10;
        }
    }

    if (key == GLUT_KEY_UP && player.isGrounded) {
        player.jump();
        player.unDuck();
    }
}


void keySpecialUp(int key, int x, int y) {
    if (key == GLUT_KEY_DOWN) {
        player.unDuck();
    }
}

void calculateDeltaTime() {
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = (currentTime - lastTime) / 1000.0f; // Convert milliseconds to seconds
    lastTime = currentTime;
}