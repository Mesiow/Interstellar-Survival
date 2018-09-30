#include "Asteroid.h"

Asteroid::Asteroid(sf::Texture * texture, sf::Vector2f direction)
{
	this->hp = 1;
	this->damage = 1;
	this->direction = direction;
	this->velocity = sf::Vector2f(0.5f, 2.0f);
	this->rotation = randomFloat(-0.5f, 0.5f);

	asteroid.setTexture(*texture);
	asteroid.setScale(0.3f, 0.3f);

    //default origin is 0, 0 which is top left of object)
	asteroid.setOrigin(sf::Vector2f(asteroid.getTextureRect().width / 2,  asteroid.getTextureRect().height / 2));

	setSpawnPos();
}

Asteroid::~Asteroid()
{

}

void Asteroid::move(const float & dt)
{
	velocity.x *= direction.x;
	velocity.y *= direction.y;

	this->position = asteroid.getPosition();

	asteroid.move(velocity * dt);

	asteroid.rotate(rotation * dt);
}

void Asteroid::setSpawnPos()
{
	float x = randomFloat(0.0f, 700.0f);
	float y = randomFloat(-200.0f, 0.0f);

	this->position.x = x;
	this->position.y = y;

	asteroid.setPosition(sf::Vector2f(x, y));
}


void Asteroid::draw(sf::RenderTarget & target)
{
	target.draw(asteroid);
}
