#pragma once

#include <SFML/Graphics.hpp>
#include <vector>


enum class ui
{
	healthBar=0,
	shieldBar,
};

class UI
{
public:
	UI();
	~UI();

	UI(const UI &other) = delete;
	UI(UI &&other) = delete;
	UI &operator=(const UI &other) = delete;

public:
	void draw(sf::RenderTarget &target);
	void init(const int hp);
	void update(const int hp);

private:
	sf::Font font;
	std::vector<sf::Text> texts;
};