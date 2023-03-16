#pragma once
#include "Controller.h"

class InputManager
{
private:
	Controller* c;
	Model* m;

public:

	InputManager(Controller* c, Model* m);

	void Handle(sf::Event event, sf::Window& window);
};

