#include "Laser.h"

Laser::Laser(sf::Texture * texture, sf::Vector2f position, sf::Vector2f direction) //direction will be either -1 or 1 //up or down
{
	this->direction = direction;
	this->position = position;
	this->velocity = sf::Vector2f(0.0f, 20.0f * direction.y); //if dir positive the laser is part of enemy else it is ours
	this->currentvelocity = velocity;

	laser.setTexture(*texture);
	laser.setPosition(position);
	laser.setScale(0.05f, 0.05f);
	laser.rotate(90);

}

Laser::~Laser()
{

}

void Laser::move(const float &dt)
{
	this->position.x = laser.getPosition().x; //track pos
	this->position.y = laser.getPosition().y;
	this->currentvelocity = velocity * dt;

	laser.move(currentvelocity);
}

void Laser::draw(sf::RenderTarget & target)
{
	target.draw(laser);
}
