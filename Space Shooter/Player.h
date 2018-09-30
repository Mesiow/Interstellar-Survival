#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Laser.h"
#include "Shield.h"
#include "Text.h"

class Player
{

public:
	Player(sf::Texture *texture, sf::Vector2f position, sf::Vector2f scale);
	~Player();

public:
	void move(const float &dt);
	void draw(sf::RenderTarget &target);
	void input();
	void initUI();

public:
	void increaseHp();
	void rechargeShield();

public: //modifiers
	void takeDmg(int dmg);
	void takeSpDmg(int dmg);
	void reverseVel(){ this->velocity = -velocity; }

public:
	bool isAlive()const { return this->Hp > 0; }


public: //accessors
	inline sf::Sprite &getPlayer() { return player; }
	inline sf::Vector2f &getPosition() { return pos; }
	inline std::vector<Bullet*> &getBullets() { return bullets; }
	inline Shield *&getShield() { return shield; }
	inline int getDmg()const { return damage; }
	inline int getHp()const { return Hp; }
	inline int getSp()const { return Sp; }

private:
	sf::Vector2f pos;
	sf::Vector2f velocity;
	sf::Vector2f direction;
	sf::Sprite player;

private:
	float maxVelocity;
	float stabilizer;
	float acceleration;

private:
    int MaxHp, Hp;
    int MaxSp, Sp;
    int damage;
	unsigned int fireTimer, maxFireTimer;
	unsigned int spTimer, spTimerMax;
	bool overheated;

private:
	std::vector<Text> texts;

private:
	Shield *shield;
	std::vector<sf::RectangleShape> ui;
	std::vector<Bullet*> bullets;

private:
	enum class UI
	{
		health=0,
		shield,
	};

};