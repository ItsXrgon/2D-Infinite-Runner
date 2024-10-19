#include "Player.h"
#include "../Globals.h"
#include "cmath"
#include <GL/glut.h>

float bodyBop = 2.0f;
float bodyBopCounter = 0.0;

Player::Player() {
    x = 100;
    y = floorHeight;
	health = 5;
	maxHealth = 5;
    width = 50;
    height = 100;
    isJumping = false;
	isDucking = false;
	isGrounded = true;
	isColliding = false;
	invincibilityDuration = 10.0f;
	isInvincible = false;
	invincibilityTimer = 0.0f;
	isDoublePoints = false;
	doublePointsDuration = 20.0f;
	doublePointsTimer = 0.0f;
}

void Player::draw() {
	int const headHeight = 30;
	int const torsoHeight = isDucking ? 25 : 45;
	int const legsHeight = isDucking ? 15 : 25;

	// Head
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < 100; i++) {
		float theta = 2.0f * M_PI * float(i) / float(100);
		float circleX = 15 * cosf(theta);
		float circleY = 15 * sinf(theta);
		glVertex2f(circleX + x + width / 2.0f, circleY + y + legsHeight + torsoHeight + 15 + bodyBop);
	}
	glEnd();

	// Body
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
	glVertex2f(x, y + legsHeight);
	glVertex2f(x, y + legsHeight + torsoHeight + bodyBop);
	glVertex2f(x + width, y + legsHeight + torsoHeight + bodyBop);
	glVertex2f(x + width, y + legsHeight);
	glEnd();

	// Shirt decoration
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(x, y + legsHeight + torsoHeight + bodyBop);
	glVertex2f(x + width, y + legsHeight + torsoHeight + bodyBop);
	glVertex2f(x + width / 2.0f, y + legsHeight + torsoHeight / 2.0f + bodyBop);
	glEnd();

	// Legs
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	// Left leg
	glVertex2f(x + 5, y);
	glVertex2f(x + 5, y + legsHeight);

	// Right leg
	glVertex2f(x + width - 5, y);
	glVertex2f(x + width - 5, y + legsHeight);
	glEnd();
}

void Player::update(float deltaTime) {
    if (isJumping) {
        y += 5.0f; 
		if (y > floorHeight + 100) isJumping = false;
    }
    else if (y > floorHeight) {
        y -= 1.5;
	}
	else if (y <= floorHeight) {
		y = floorHeight;
		isGrounded = true;
	}
	bodyBopCounter += 0.1;
	if (bodyBopCounter >= 2.0) {
		bodyBop = -bodyBop;
		bodyBopCounter = 0;
	}

	if (isInvincible) {
		invincibilityTimer -= deltaTime;
		if (invincibilityTimer <= 0) {
			isInvincible = false;
		}
	}

	if (isDoublePoints) {
		doublePointsTimer -= deltaTime;
		if (doublePointsTimer <= 0) {
			isDoublePoints = false;
		}
	}
}

void Player::jump() {
	if (!isJumping) { 
		isJumping = true;
		isGrounded = false;
		height = 100;
	}
}

void Player::duck() {
	if (!isJumping) { 
		isDucking = true;
		isJumping = false;
		isGrounded = true;
		y = floorHeight;
		height = 70;
	}
}

void Player::unDuck() {
	if (isDucking) {
		isDucking = false;
		height = 100;
	};
}


void Player::handleObjectCollision() {
	if (invincibilityTimer <= 0) {
		health -= 1;

		invincibilityTimer = 5.0f;

		if (health <= 0) {
		}
	}
}

void Player::handleCollectibleCollision() {
	if (isDoublePoints) {
		score += 2;
	}
	else {
		score++;
	}
}

Rect Player::getBoundingBox() {
	return Rect{ x, y, width, height };
}