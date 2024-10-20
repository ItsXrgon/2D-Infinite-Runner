#pragma once
#include <string>
#include <functional>

class Button {
protected:
	std::string text;
	float x, y;
	float width;
	float height;

public:
	Button();
	Button(std::string text, float x, float y, float width, float height);
	~Button() = default;
	void draw();
	bool isClicked(float mouseX, float mouseY);
	void displayText(std::string text, float x, float y);
};


