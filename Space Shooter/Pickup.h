#pragma once
#include <SFML/Graphics.hpp>

class Pickup
{
public:
	virtual ~Pickup(){}

public:
	virtual void update(const float &dt) = 0;
	virtual void draw(sf::RenderTarget &target) = 0;

public:
	virtual inline sf::Vector2f &getPosition() = 0;
	virtual inline sf::RectangleShape &getPickup() = 0;
};