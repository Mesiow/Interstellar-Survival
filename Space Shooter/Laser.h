#pragma once
#include "Bullet.h"

class Laser : public Bullet
{

public:
	Laser(sf::Texture *texture, sf::Vector2f position, sf::Vector2f direction);
	~Laser();

public:
	void move(const float &dt)override;
	void draw(sf::RenderTarget &target)override;

public:
	inline sf::Vector2f &getPosition()override { return position; }
	inline sf::Sprite &getBullet()override { return laser; }
	inline sf::Vector2f &getVelocity()override { return velocity; }
	inline sf::Vector2f getNormDir()override { return normalize(this->currentvelocity, vectorLength(this->currentvelocity)); }

private:
	sf::Sprite laser;

private:
	sf::Vector2f currentvelocity;
	sf::Vector2f direction;
	sf::Vector2f velocity;
	sf::Vector2f position;
	float initialvelocity;
};