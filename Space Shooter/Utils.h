#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

enum class Texture
{
	background = 0,
	player,
	enemy,
	laser,
	asteroid,
	particle,
	shield,
};

enum class Font
{
	optimus = 0,
	firstInLine,
};

enum class Sound
{
	laser = 0,
	shieldHit,
};

void save_to_file(int score);
int load_score_from_file();

int randomInt(int low, int high);
float randomFloat(float low, float high);

float vectorLength(sf::Vector2f v);
sf::Vector2f normalize(sf::Vector2f v, float length);