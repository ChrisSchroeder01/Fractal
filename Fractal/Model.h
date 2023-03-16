#pragma once
#include <SFML/Graphics.hpp>

class Model
{
private:
	int xOffset = 0, yOffset = 0;
	int zoom = 200;

public:
	Model(sf::RenderWindow* window);

	int getXOffset();
	int getYOffset();
	int getZoom();

	void changeZoomBy(int amount);
	void changeOffsetBy(int ax, int ay);

	int dragxOffset;
	int dragyOffset;

	int lastxOffset;
	int lastyOffset;
	int lastzoom;

	int MAX_ITERAIONS = 200;

	sf::RenderWindow* window;

	bool scrolling = false;
	sf::Clock lastScrolled;
	int zoomChange = 0;

	bool moving = false;
	sf::Vector2f newPos, oldPos, deltaPos;

	sf::Texture frame;
	sf::Sprite sprite, actionSprite;
	sf::Color tMask = sf::Color(255, 255, 255, 128);
};

