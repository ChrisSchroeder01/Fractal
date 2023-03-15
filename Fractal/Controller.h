#pragma once
#include "Model.h"
#include <SFML/Graphics.hpp>
#include "Viewer.h"
#include "OpenCL_Kernel.h"


class Controller
{
private:
	Model* m;
	Viewer* v;
	sf::Image image;
	OpenCL_Kernel* kernel;

public:

	Controller(Model* m);

	void LoadImg(sf::Texture& screen);
	void SaveImg(sf::Texture& screen);
	bool NeedToRedraw();

	void Zoom(int direction);
	void calculateArea(int xPos, int yPos, int width, int height);

	void Render(int width, int height);

	void Exit();
};

