#pragma once
#include <SFML/Graphics.hpp>
#include "Utils.h"

class Asteroid
{
public:
	Asteroid(sf::Texture *texture, sf::Vector2f direction);
	~Asteroid();

public:
	void move(const float &dt);
	void draw(sf::RenderTarget &target);

public:
	void setSpawnPos();

public:
	inline unsigned int getDmg()const { return damage; }
	inline sf::Vector2f &getPosition() { return position; }
	inline sf::Sprite &getAsteroid() { return asteroid; }

private:
	sf::Sprite asteroid;
	
private:
	sf::Vector2f position;
	sf::Vector2f direction;
	sf::Vector2f velocity;

private:
	unsigned int hp;
	unsigned int damage;
	float rotation;

};