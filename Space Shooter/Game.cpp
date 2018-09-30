#include "Game.h"

sf::RenderWindow *Game::window;
State *Game::current;

Game::Game()
{
	window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Interstellar Survival", sf::Style::Close);
	window->setFramerateLimit(60);

	initState();
}

Game::~Game()
{
	delete menu;
	delete window;
}

void Game::run()
{
	sf::Clock timer;
	sf::Time tickRate;
	float multiplier = 60.0f;


	while (window->isOpen())
	{
		tickRate = timer.restart();

		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				window->close();
			}
		}
		float dt = (float)tickRate.asMilliseconds() / 1000;

		input();
		update(dt * multiplier);
		render();
		display();
	}
}

void Game::initState()
{
	states.push_back(State(states::MENU));
	states.push_back(State(states::PLAYING));

	current = &states[states::MENU];

	if (current->getState() == states::MENU)
		menu = new Menu();

}

void Game::update(float dt)
{
	window->clear();

	if (current->getState() == states::MENU)
		menu->update();
	else if (current->getState() == states::PLAYING)
		world->update(dt);
	else if (current->getState() == states::EXIT)
		window->close();
}

void Game::render()
{

	if (current->getState() == states::MENU)
		menu->draw(*window);
	else if (current->getState() == states::PLAYING)
		world->render(*window);
}


void Game::display()
{
	window->display();
}

void Game::input()
{
	checkState();
	if(current->getState()==states::PLAYING)
		world->input();
}

void Game::checkState()
{
	if (current->getState() == states::MENU)
	{
		menu->setHSText(load_score_from_file());

		if (menu->isButtonPressed())
		{
			if (menu->getButtonPressed() == menu->buttons::PLAY)
			{
				world = new World();
				current->setState(states::PLAYING);
			}
			else
				current->setState(states::EXIT);
		}
	}
}

