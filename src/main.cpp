#include <vector>
#include <cstdlib>
#include <ctime>
#include "SceneManager/SceneManager.h"
#include "SceneManager/scenes/menu/Menu.h"
#include "SceneManager/scenes/play/Play.h"
#include "Globals.h"
#include <GL/glut.h>

float lastTime = 0.0f;

void keySpecial(int key, int x, int y);
void keySpecialUp(int key, int x, int y);
void handleMouseClick(int button, int state, int x, int y);
void loadSoundFiles();

void loadSoundFiles() {
    audioManager.addFile("background-play", "sounds/background-play.wav");
    audioManager.addFile("background-win", "sounds/background-win.wav");
    audioManager.addFile("background-loss", "sounds/background-loss.wav");
    audioManager.addFile("coin", "sounds/coin.wav");
    audioManager.addFile("damage", "sounds/damage.wav");
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    sceneManager.draw();
    glFlush();
}

void update(int value) {
    glutPostRedisplay();
    float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    float deltaTime = currentTime - lastTime;
    lastTime = currentTime;

	sceneManager.update(deltaTime);
    glutTimerFunc(16, update, 0);  // ~16ms (~60fps)
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    loadSoundFiles();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Infinite Runner");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0, windowWidth, 0, windowHeight);

    glutDisplayFunc(display);
    glutSpecialFunc(keySpecial);
    glutSpecialUpFunc(keySpecialUp);
    glutMouseFunc(handleMouseClick);
    glutTimerFunc(0, update, 0);

    sceneManager.setActiveScene(new Menu());

    lastTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

    glutMainLoop();
    return 0;
}

void keySpecial(int key, int x, int y) {
	sceneManager.keySpecial(key, x, y);
}


void keySpecialUp(int key, int x, int y) {
    sceneManager.keySpecialUp(key, x, y); 
}

void handleMouseClick(int button, int state, int x, int y) {
    y = windowHeight - y;

    sceneManager.handleMouseClick(button, state, x, y);
}