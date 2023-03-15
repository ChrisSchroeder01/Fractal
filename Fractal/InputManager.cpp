#include "InputManager.h"

InputManager::InputManager(Controller* c)
{
	this->c = c;
}

void InputManager::Handle(sf::Event event)
{
	switch (event.type)
	{
    case(sf::Event::Closed):
        c->Exit();
    case(sf::Event::MouseWheelMoved):

	default:
		break;
	}


    /*
    // Mouse Wheel Moved
    if (event.type == sf::Event::MouseWheelMoved)
    {
        scrolling = true;
        lastScrolled.restart();
        changeZoomBy += event.mouseWheel.delta;
    }

    // Mouse Button Pressed
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == 0)
        {
            moving = true;
            oldPos = sf::Vector2f(sf::Mouse::getPosition(window));
        }
    }

    // Mouse Button Released
    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == 0)
        {
            std::cout << "Change xy by - x: " << deltaPos.x << " y: " << deltaPos.y << std::endl;
            m->changeXYBy(deltaPos.x, deltaPos.y);
            moving = false;
        }
    }

    // Mouse Moved
    if (event.type == sf::Event::MouseMoved) {
        if (!moving)
            break;
        newPos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
        deltaPos = oldPos - newPos;
    }*/
}
