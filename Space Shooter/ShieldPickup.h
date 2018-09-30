#pragma once
#include "Pickup.h"


class ShieldPickup : public Pickup
{
public:
	ShieldPickup(sf::Vector2f position)
	{
		this->position = position;
		this->velocity = sf::Vector2f(0.0f, 0.8f);
		this->direction = sf::Vector2f(0.0f, 1.0f);

		velocity.x += direction.x;
		velocity.y += direction.y;

		pickup.setPosition(position);
		pickup.setSize(sf::Vector2f(5, 15));
		pickup.setFillColor(sf::Color(40, 80, 255, 255));
		pickup.setOutlineColor(sf::Color::Black);
	}
	~ShieldPickup(){}

public:
	void update(const float &dt)override
	{
		pickup.move(velocity * dt);
		pickup.rotate(0.5f * dt);
	}
	void draw(sf::RenderTarget &target)override
	{
		target.draw(pickup);
	}


public:
	inline sf::Vector2f &getPosition() { return position; }
	//inline sf::Sprite &getPickup() { return pickup; }
	inline sf::RectangleShape &getPickup() { return pickup; }

private:
	sf::RectangleShape pickup;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f direction;
};