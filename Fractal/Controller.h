#pragma once
#include "Model.h"
#include <SFML/Graphics.hpp>
#include "Viewer.h"

class Controller
{
private:
	Model* m;
	Viewer* v;
	sf::Image image;

public:

	Controller(Model* m);

	void LoadImage(sf::Texture& screen);
	void SaveImage(sf::Texture& screen);
	bool NeedToRedraw();

	void Zoom(int direction);
	void calculateArea(int xPos, int yPos, int width, int height);

	void Render(int width, int height);

	void Exit();
};

