#include "Enemy.h"
#include "World.h"

class World;

Enemy::Enemy(sf::Texture *texture)
{
	this->hp = 2;
	this->damage = 2;
	this->velocity = sf::Vector2f(0.0f, 1.2f);
	this->acceleration = 0.001f;

	enemy.setTexture(*texture);
	enemy.setScale(sf::Vector2f(0.04f, 0.04f));
	enemy.rotate(180.0f);


	setSpawnPos();
}

Enemy::~Enemy()
{

}

void Enemy::update(const float & dt)
{
	
	int ran = randomInt(1, 100);
	if (ran == 5)
	{
		bullets.push_back(new Laser(&World::textures[(int)Texture::laser], sf::Vector2f(enemy.getPosition().x - 30.0f, enemy.getPosition().y - 25.0f), sf::Vector2f(0.0f, 1.0f)));
	}

	move(dt);
}

void Enemy::move(const float &dt)
{
	this->pos = enemy.getPosition();

	enemy.move(velocity * dt);
}

void Enemy::setSpawnPos()
{
	float x = randomFloat(0.0f, 700.0f);
	float y = randomFloat(-100.0f, 0.0f);

	this->pos.x = x;
	this->pos.y = y;

	enemy.setPosition(sf::Vector2f(pos));
}

void Enemy::draw(sf::RenderTarget &target)
{
	target.draw(enemy);
}
