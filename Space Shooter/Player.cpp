#include "Player.h"
#include "World.h"

class World;

Player::Player(sf::Texture * texture, sf::Vector2f position, sf::Vector2f scale)
{

	initUI();

	this->MaxHp = 15;
	this->Hp = MaxHp;
	this->MaxSp = 100;
	this->Sp = MaxSp;

	this->damage = 1;
	this->fireTimer = 0;
	this->maxFireTimer = 25;
	this->pos = position;
	this->velocity = sf::Vector2f(0.0f, 0.0f);
	this->acceleration = 1.0f;
	this->maxVelocity = 50.0f;
	this->stabilizer = 0.2f;

	player.setTexture(*texture);
	player.setPosition(position);
	player.setScale(scale);

	shield = new Shield(&World::textures[(int)Texture::shield], sf::Vector2f(player.getPosition().x - 38.0f, player.getPosition().y - 40.0f), sf::Vector2f(0.3f, 0.3f));
}

Player::~Player()
{
	shield = nullptr;
	delete shield;
}

void Player::move(const float &dt)
{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			direction.y = -1.0f;

			if (velocity.y > -maxVelocity && direction.y < 0)
				velocity.y += direction.y * acceleration;
			
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			direction.y = 1.0f;

			if (velocity.y < maxVelocity && direction.y > 0)
				velocity.y += direction.y * acceleration;
			
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			direction.x = -1.0f;

			if (velocity.x > -maxVelocity && direction.x < 0)
				velocity.x += direction.x * acceleration;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			direction.x = 1.0f;
		
			if (velocity.x < maxVelocity && direction.x > 0)
				velocity.x += direction.x * acceleration;
		}

		if (velocity.x > 0) //stablize ship
		{
			velocity.x -= stabilizer;
			if (velocity.x < 0.0f)
				velocity.x = 0.0f;
		}
		else if (velocity.x < 0)
		{
			velocity.x += stabilizer;
			if (velocity.x > 0.0f)
				velocity.x = 0.0f;
		}
	    if (velocity.y > 0)
		{
			velocity.y -= stabilizer;
			if (velocity.y < 0.0f)
				velocity.y = 0.0f;
		}
		else if (velocity.y < 0)
		{
			velocity.y += stabilizer;
			if (velocity.y > 0.0f)
				velocity.y = 0.0f;
		}
		player.move(velocity * dt);

		if(shield!=nullptr)
			shield->getShield().move(velocity * dt);

		this->pos = player.getPosition(); //TRACK positions

}

void Player::input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (fireTimer >= maxFireTimer)
		{
			World::sounds[(int)Sound::laser].play();
			bullets.push_back(new Laser(&World::textures[(int)Texture::laser], sf::Vector2f(pos.x + 50.0f, pos.y), sf::Vector2f(0.0f, -1.0f)));
			fireTimer = 0;
		}
	}
	fireTimer++;
}

void Player::initUI()
{
	ui.push_back(sf::RectangleShape());
	ui[(int)UI::health].setFillColor(sf::Color::Red);
	ui[(int)UI::health].setPosition(10, 10);
	ui[(int)UI::health].setSize(sf::Vector2f(15, 10));
	texts.push_back(Text(&World::fonts[(int)Font::firstInLine], "HP", sf::Vector2f(10,20),  20));

	ui.push_back(sf::RectangleShape());
	ui[(int)UI::shield].setFillColor(sf::Color::Blue);
	ui[(int)UI::shield].setPosition(690, 10);
	ui[(int)UI::shield].setSize(sf::Vector2f(100, 10));
	texts.push_back(Text(&World::fonts[(int)Font::firstInLine], "SP", sf::Vector2f(770, 20), 20));
}

void Player::increaseHp()
{
	this->Hp += 5;

	float x = ui[(int)UI::health].getSize().x;
	ui[(int)UI::health].setSize(sf::Vector2f(x + 5.0f, 10));
}

void Player::rechargeShield()
{
	float x = ui[(int)UI::shield].getSize().x;
	if (shield != nullptr)//if we have a shield
	{
		ui[(int)UI::shield].setPosition(690, 10);
		ui[(int)UI::shield].setSize(sf::Vector2f(x + 5.0f, 10));
	}
	else
	{ //if shield gone create new
		shield = new Shield(&World::textures[(int)Texture::shield], sf::Vector2f(player.getPosition().x - 38.0f, player.getPosition().y - 40.0f), sf::Vector2f(0.3f, 0.3f));
		ui[(int)UI::shield].setPosition(690, 10);
		ui[(int)UI::shield].setSize(sf::Vector2f(x + 5.0f, 10));
	}

		
}

void Player::takeDmg(int dmg)
{
	this->Hp -= dmg;
	float x = ui[(int)UI::health].getSize().x;

	if (x <= 0.0f)
		return;

	ui[(int)UI::health].setSize(sf::Vector2f(x-dmg, 10));
}

void Player::takeSpDmg(int dmg) //if hit with shield on
{
	this->Sp -= dmg;
	float x = ui[(int)UI::shield].getSize().x;

	ui[(int)UI::shield].setSize(sf::Vector2f(x - 15.0f, 10)); //else shield is hit

	if (x <= 0.0f) //when shield hits 0 recharge
	{
		ui[(int)UI::shield].setSize(sf::Vector2f(0.0f, 0.0f));
		delete shield;
		shield = nullptr;
		return;
	}

}

void Player::draw(sf::RenderTarget & target)
{
	for (int i = 0; i < ui.size(); i++)
		target.draw(ui[i]);

	for (int i = 0; i < texts.size(); i++)
		texts[i].draw(target);

	target.draw(player);

	if(shield!=nullptr)
		shield->draw(target);
}
