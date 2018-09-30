#include "MainMenu.h"
#include "Game.h"
class Game;

Menu::Menu()
{
	font.loadFromFile("Font/First.otf");
	backTex.loadFromFile("Sprites/MenuBackground.jpg");
	music.openFromFile("Sounds/MenuTrack.wav");

	background.setTexture(backTex);
	background.setPosition(0, 0);
	music.play();
	init();
}

Menu::~Menu()
{

}

void Menu::init()
{
	texts.push_back(Text(&font, "Play", sf::Vector2f(Game::window->getSize().x / 2 - 50, Game::window->getSize().y / 2 - 70), 60));
	texts.push_back(Text(&font, "High Score: ", sf::Vector2f(Game::window->getSize().x/2 - 400, Game::window->getSize().y/2 + 260 ), 25)); //bottom left 
	texts.push_back(Text(&font, "Exit", sf::Vector2f(Game::window->getSize().x / 2 - 40, Game::window->getSize().y / 2 - 10), 60));
	texts.push_back(Text(&font, std::to_string(this->highscore), sf::Vector2f(Game::window->getSize().x / 2 - 280, Game::window->getSize().y / 2 + 260), 25));
}

void Menu::update()
{
	texts[3].setString(std::to_string(this->highscore));
	mouseHovering();
}

void Menu::draw(sf::RenderTarget & target)
{
	target.draw(background); 

	for (int i = 0; i < texts.size(); i++)
		texts[i].draw(target);
	
}

bool Menu::isButtonPressed()
{
	sf::Vector2f mousepos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(Game::getWindow())); //convert mousepos to float

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
			if (texts[buttons::PLAY].getGlobalBounds().contains(mousepos)) //if play is pressed
			{
				buttonPressed = buttons::PLAY;
				return true;
			}
			else if (texts[buttons::HIGHSCORE].getGlobalBounds().contains(mousepos))
			{
				buttonPressed = buttons::HIGHSCORE;
				return true;
			}
			else if (texts[buttons::EXIT].getGlobalBounds().contains(mousepos))
			{
				buttonPressed = buttons::EXIT;
				return true;
			}
	}
	return false;
}

void Menu::mouseHovering()
{
	sf::Vector2f mousepos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(Game::getWindow()));

	if (texts[buttons::PLAY].getGlobalBounds().contains(mousepos))
		texts[buttons::PLAY].setColor(sf::Color::Red);
	else if (texts[buttons::EXIT].getGlobalBounds().contains(mousepos))
		texts[buttons::EXIT].setColor(sf::Color::Red);
	else
	{
		for (int i = 0; i < texts.size(); i++)
			texts[i].setColor(sf::Color::White);
	}
}
