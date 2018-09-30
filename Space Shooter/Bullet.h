#pragma once
#include <SFML/Graphics.hpp>
#include "Utils.h"

class Bullet //abstract class
{
public:
	virtual ~Bullet(){}

public:
	virtual void move(const float &dt) = 0;
	virtual void draw(sf::RenderTarget &target) = 0;

public:
	virtual inline sf::Vector2f &getPosition() = 0;
	virtual inline sf::Sprite &getBullet() = 0;
	virtual inline sf::Vector2f getNormDir() = 0;
	virtual inline sf::Vector2f &getVelocity() = 0;

};