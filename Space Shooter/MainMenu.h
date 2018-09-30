#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Text.h"


class Menu
{
public:
	Menu();
	~Menu();

public:
	void init();
	void update();
	void draw(sf::RenderTarget &target);
	void drawButtons(sf::RenderTarget &target);
	void mouseHovering();

public:
	bool isButtonPressed();

public:
	enum buttons { PLAY = 0, HIGHSCORE, EXIT, };

public:
	buttons getButtonPressed()const { return buttonPressed; }


public:
	void setHSText(const int score) { this->highscore = score; }

private:
	sf::Music music;
	sf::Texture backTex;
	sf::Sprite background;

private:
	sf::Font font;
	std::vector<Text> texts;
	buttons buttonPressed;

private:
	int highscore;
};