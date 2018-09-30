#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
class Text 
{
public:
	Text(sf::Font *font, 
		const std::string &text, 
		sf::Vector2f position, 
		int characterSize)
	{
		this->string = text;
		this->text.setFont(*font);
		this->text.setCharacterSize(characterSize);
		this->text.setFillColor(sf::Color::White);
		this->text.setString(text);
		this->text.setPosition(position);
	}
	~Text(){}

public:
	void draw(sf::RenderTarget &target)const
	{
		target.draw(text);
	}
	
public:
	void setColor(sf::Color color) { text.setFillColor(color); }
	void setString(const std::string &text) { this->text.setString(text); }

public:
	inline sf::Vector2f getPosition()const { return text.getPosition(); }
	inline sf::FloatRect getGlobalBounds()const { return text.getGlobalBounds(); }


private:
	std::string string;
	sf::Text text;
	sf::Font *font;
};