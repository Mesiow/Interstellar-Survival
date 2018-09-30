#pragma once
#include <SFML/Graphics.hpp>
#include "Utils.h"
#include "Bullet.h"

class Enemy
{

public:
	Enemy(sf::Texture *texture);
    ~Enemy();

public:
	void update(const float &dt);
	void move(const float &dt);
	void draw(sf::RenderTarget &target);

public:
	void setSpawnPos();

public:
	void takeDmg(int dmg) { this->hp -= dmg; }

public:
	bool isAlive()const { return hp > 0; }
	inline unsigned int getHp()const { return hp; }
	inline unsigned int getDmg()const { return damage; }
	inline sf::Vector2f &getPosition() { return pos; }
	inline sf::Sprite &getEnemy() { return enemy; }
	inline std::vector<Bullet*> &getBullets() { return bullets; }

private:
	sf::Sprite enemy;

private:
	sf::Vector2f pos;
	sf::Vector2f direction;
	sf::Vector2f velocity;
	std::vector<Bullet*> bullets;

private:
	unsigned int hp;
	unsigned int damage;
	float acceleration;

};
