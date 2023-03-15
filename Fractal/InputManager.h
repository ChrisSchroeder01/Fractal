#pragma once
#include "Controller.h"

class InputManager
{
private:
	Controller* c;

public:

	InputManager(Controller* c);

	void Handle(sf::Event event);
};

