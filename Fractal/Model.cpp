#include "Model.h"



Model::Model(sf::RenderWindow* window)
{
	this->window = window;
	this->frame.create(window->getSize().x, window->getSize().y);
	this->sprite.setTexture(this->frame);
	this->actionSprite.setTexture(this->frame);

	sf::Image img;
	img = this->frame.copyToImage();
	for (int i = 0; i < 100; i++)
	{
		img.setPixel(i, i, sf::Color(255, 0, 0, 255));
	}
	this->frame.loadFromImage(img);
	this->xOffset = window->getSize().x / 2;
	this->yOffset = window->getSize().y / 2;


}

int Model::getXOffset()
{
	return this->xOffset;
}

int Model::getYOffset()
{
	return this->yOffset;
}

int Model::getZoom()
{
	return this->zoom;
}

void Model::changeZoomBy(int amount)
{
	this->zoom += amount;
}

void Model::changeOffsetBy(int ax, int ay)
{
	this->xOffset -= ax;
	this->yOffset -= ay;
}
