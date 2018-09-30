#include "UI.h"

UI::UI()
{
	font.loadFromFile("Font/Optimus.ttf");
}

UI::~UI()
{

}

void UI::init(const int hp)
{
	texts.push_back(sf::Text());
	texts[(int)ui::healthBar].setFont(font);
	texts[(int)ui::healthBar].setCharacterSize(20);
	texts[(int)ui::healthBar].setPosition(20, 20);
	texts[(int)ui::healthBar].setString("Health: " + std::to_string(hp) + "/" + "100");
}

void UI::update(const int hp)
{
	texts[(int)ui::healthBar].setString("Health: " + std::to_string(hp) + "/" + "100");
}


void UI::draw(sf::RenderTarget & target)
{
	for (int i = 0; i < texts.size(); i++)
		target.draw(texts[i]);
}

