#pragma once
#include <SFML/Graphics.hpp>
#include "World.h"
#include "State.h"
#include "MainMenu.h"

#define WIDTH 800
#define HEIGHT 600

class Game
{
public:
	Game();
	~Game();

	Game(const Game &other) = delete;
	Game(const Game &&other) = delete;
	Game &operator=(const Game &other) = delete;

public:
	void run();
	void initState();

private:
	void update(float dt);
	void display();
    void render();
	void input();
	void checkState();

public:
	static sf::RenderWindow &getWindow() { return *window; }
  

public:
    static sf::RenderWindow *window;
	static State *current;
	
private:
	sf::View view;
	World *world;

private:
	Menu *menu;
	std::vector<State> states;

};