#include "InputManager.h"

InputManager::InputManager(Controller* c, Model* m)
{
	this->c = c;
    this->m = m;
}

void InputManager::Handle(sf::Event event, sf::Window &window)
{
	switch (event.type)
	{
    case(sf::Event::Closed):
        c->Exit();
        break;
    case(sf::Event::MouseWheelMoved):
        this->m->scrolling = true;
        this->m->lastScrolled.restart();
        this->m->zoomChange += event.mouseWheel.delta * 5;
        break;
    case(sf::Event::MouseButtonPressed):
        if (event.mouseButton.button == 0)
        {
            this->m->moving = true;
            this->m->oldPos = sf::Vector2f(sf::Mouse::getPosition(window));
        }
        break;
    case(sf::Event::MouseButtonReleased):
        if (event.mouseButton.button == 0)
        {
            std::cout << "Change xy by - x: " << this->m->deltaPos.x << " y: " << this->m->deltaPos.y << std::endl;
            c->ChangeOffset(this->m->deltaPos.x, this->m->deltaPos.y);
            this->m->moving = false;
        }
        break;
    case(sf::Event::MouseMoved):
        if (!this->m->moving)
            break;
        this->m->newPos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
        this->m->deltaPos = this->m->oldPos - this->m->newPos;
        break;
	default:
		break;
	}
}

void InputManager::Handle()
{
    if (this->m->scrolling && this->m->lastScrolled.getElapsedTime().asMilliseconds() > 500)
    {
        this->m->scrolling = false;
        this->c->Zoom(this->m->zoomChange);

        std::cout << "Zoom: " << this->m->zoomChange << std::endl;

        this->m->zoomChange = 0;
    }
}
