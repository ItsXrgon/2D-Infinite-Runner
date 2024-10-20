#include "Button.h"
#include <GL/glut.h>

Button::Button() 
	: text("h"), x(0), y(0), width(0), height(0) {}

Button::Button(std::string text, float x, float y, float width, float height)
	: text(text), x(x), y(y), width(width), height(height) {}

void Button::draw() {
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(x, y, 0.0f);
	glVertex3f(x + width, y, 0.0f);
	glVertex3f(x + width, y - height, 0.0f);
	glVertex3f(x, y - height, 0.0f);
	glEnd();

	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_QUADS);
	glVertex3f(x, y, 0.0f);
	glVertex3f(x + width, y, 0.0f);
	glVertex3f(x + width, y - height, 0.0f);
	glVertex3f(x, y - height, 0.0f);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	displayText(text, x + width / 2, y - height / 2);
}

bool Button::isClicked(float mouseX, float mouseY) {
	return mouseX >= x && mouseX <= x + width &&
		mouseY <= y && mouseY >= y - height;
}

void Button::displayText(std::string text, float x, float y)
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos2f(x, y);
	for (int i = 0; i < text.size(); ++i)
	{
		char c = text[i];
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}
}