#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Asteroid.h"
#include "Particle.h"
#include "UI.h"
#include "Text.h"
#include "ShieldPickup.h"
#include "HpPickup.h"


class World 
{
public:
	World();
	~World();

public://updating
	void input();
	void update(float dt);
	void updateEntities(const float &dt);
	void updateBullets(const float &dt);
	void updatePlayer(const float &dt);
	void updateEnemies(const float &dt);
	void checkState();

public://rendering
	void render(sf::RenderTarget &target)const;
	void renderBackGround(sf::RenderTarget &target)const;
	void renderBullets(sf::RenderTarget &target)const;
	void renderEntities(sf::RenderTarget &target)const;
	void loadTextures();
	void loadSounds();
	void loadFonts();
	void initEntities();
	void initText();

public://logic
	void logic();
	void windowCollision();
	void collision();
	void enemyCollision();
	void playerCollision();
	void laserCollision();
	void backgroundScrolling();
	void spawnEnemies();
	void spawnAsteroids();

public:
	void freeObjects();




public:
	static std::vector<sf::Texture> textures;
	static std::vector<sf::Font> fonts;
	static std::vector<sf::Sound> sounds;
	static std::vector<sf::SoundBuffer> soundBuffers;
	static int scorenum;
	static sf::Text score;
	Text *scoreText;

private:
	Player *player;
	std::vector<Enemy> enemies;
	std::vector<Asteroid> asteroids;
	std::vector<Particle> particles;
	std::vector<Pickup*> shieldPickups;
	std::vector<Pickup*> hpPickups;

private:
	sf::Vector2f backgroundDirection;
	sf::Sprite background;
	std::vector<sf::Sprite> backgrounds;
};