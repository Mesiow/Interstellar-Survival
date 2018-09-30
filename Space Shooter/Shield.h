#pragma once
#include <SFML/Graphics.hpp>
class Shield
{
public:
	Shield(sf::Texture *texture, sf::Vector2f position, sf::Vector2f scale)
	{
		this->position = position;
		shield.setTexture(*texture);
		shield.setPosition(position);
		shield.setScale(scale);
	}
	~Shield(){}

public:
	inline void draw(sf::RenderTarget &target) { target.draw(shield); }

public:
	void setPosition(sf::Vector2f pos) { this->position = pos; }

public:
	inline sf::FloatRect getGlobalBounds()const { return shield.getGlobalBounds(); }
	inline sf::Vector2f &getPosition() { return this->position; }
	inline sf::Sprite &getShield() { return shield; }

private:
	sf::Vector2f position;
	sf::Sprite shield;
};