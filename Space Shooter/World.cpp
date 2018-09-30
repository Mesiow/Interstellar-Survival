#include "World.h"
#include "Game.h"
#include <iostream>

class Game;

std::vector<sf::Texture> World::textures;
std::vector<sf::Font> World::fonts;
std::vector<sf::SoundBuffer> World::soundBuffers;
std::vector<sf::Sound> World::sounds;

sf::Text World::score;
int World::scorenum;

World::World()
{
	loadTextures();
	loadSounds();
	loadFonts();
	initEntities();
	initText();
	this->scorenum = 0;
}

World::~World()
{
	delete scoreText;
	delete player;
}

void World::loadTextures()
{
	//textures
	textures.push_back(sf::Texture());
	textures[(int)Texture::background].loadFromFile("Sprites/spaceBackground.png");

	textures.push_back(sf::Texture());
	textures[(int)Texture::player].loadFromFile("Sprites/ship.png");

	textures.push_back(sf::Texture());
	textures[(int)Texture::enemy].loadFromFile("Sprites/enemy.png");

	textures.push_back(sf::Texture());
	textures[(int)Texture::laser].loadFromFile("Sprites/laser.png");

	textures.push_back(sf::Texture());
	textures[(int)Texture::asteroid].loadFromFile("Sprites/asteroid.png");

	textures.push_back(sf::Texture());
	textures[(int)Texture::particle].loadFromFile("Sprites/Particle03.png");

	textures.push_back(sf::Texture());
	textures[(int)Texture::shield].loadFromFile("Sprites/shield.png");
}

void World::loadSounds()
{
	soundBuffers.push_back(sf::SoundBuffer());
	soundBuffers[(int)Sound::laser].loadFromFile("Sounds/laser.wav");

	soundBuffers.push_back(sf::SoundBuffer());
	soundBuffers[(int)Sound::shieldHit].loadFromFile("Sounds/shieldHit.wav");

	//bind buffer to sound object
	sounds.push_back(sf::Sound());
	sounds[(int)Sound::laser].setBuffer(soundBuffers[(int)Sound::laser]);
	sounds[(int)Sound::laser].setVolume(50.0f);

	sounds.push_back(sf::Sound());
	sounds[(int)Sound::shieldHit].setBuffer(soundBuffers[(int)Sound::shieldHit]);
	sounds[(int)Sound::shieldHit].setVolume(50.0f);
}

void World::loadFonts()
{
	fonts.push_back(sf::Font());
	fonts[(int)Font::optimus].loadFromFile("Font/Optimus.ttf");

	fonts.push_back(sf::Font());
	fonts[(int)Font::firstInLine].loadFromFile("Font/First.otf");
}

void World::initText()
{
	scoreText = new Text(&fonts[(int)Font::firstInLine], "Score: ", sf::Vector2f(5, 570), 20);
	score.setFont(fonts[(int)Font::firstInLine]);
	score.setPosition(scoreText->getPosition().x + 60, scoreText->getPosition().y);
	score.setCharacterSize(20);
	score.setString(std::to_string(scorenum));
}

void World::initEntities()
{
	backgroundDirection = sf::Vector2f(0.0f, 1.0f);

	player = new Player(&textures[(int)Texture::player], sf::Vector2f(400.0f, 400.0f), sf::Vector2f(0.1f, 0.1f));


	for (int i = 0; i < 4; i++)
		enemies.push_back(Enemy(&textures[(int)Texture::enemy])); //spawn enemies


	float dirx = randomFloat(0.0f, 0.5f); //random float from 0.0f - 0.2f
	for (int i = 0; i < 4; i++)
		asteroids.push_back(Asteroid(&textures[(int)Texture::asteroid], sf::Vector2f(dirx, 1.0f)));
	

	background.setTexture(textures[(int)Texture::background]);
	background.setPosition(sf::Vector2f(0.0f, 0.0f));
	background.scale(sf::Vector2f(Game::window->getSize().x / 512.0f, Game::window->getSize().y / 512.0f)); //fit background sprite to window size

	backgrounds.push_back(background); //default
	background.setPosition(sf::Vector2f(0.0f, -600.0f));
	backgrounds.push_back(background);  //clone

}

void World::input()
{
	if (!player->isAlive())
		return;

	player->input();
}

void World::checkState()
{
	if (!player->isAlive())
	{
		save_to_file(scorenum); //save the score we died with to file if its larger than previous score
		Game::current->setState(states::MENU); //if player dead go to the menu
	}
}


void World::update(float dt)
{
	checkState();
	logic();

	updatePlayer(dt);
	updateEnemies(dt);
	updateBullets(dt);
	updateEntities(dt);

	score.setString(std::to_string(scorenum));
	freeObjects();
}

void World::updateEntities(const float & dt)
{
	for (std::size_t i = 0; i < asteroids.size(); ++i)
		asteroids[i].move(dt);

	for (std::size_t i = 0; i < particles.size(); ++i)
		particles[i].update(dt);

	for (std::size_t i = 0; i < shieldPickups.size(); ++i)
		shieldPickups[i]->update(dt);

	for (std::size_t i = 0; i < hpPickups.size(); ++i)
		hpPickups[i]->update(dt);

}

void World::updateBullets(const float & dt)
{

	for (std::size_t i = 0; i < player->getBullets().size(); ++i)
		player->getBullets()[i]->move(dt);

	for (std::size_t i = 0; i<enemies.size(); ++i) //update enemy lasers
	{
		for (std::size_t k = 0; k < enemies[i].getBullets().size(); ++k)
			enemies[i].getBullets()[k]->move(dt);
	}
}

void World::updatePlayer(const float & dt)
{
	player->move(dt);
}

void World::updateEnemies(const float & dt)
{
	for (std::size_t i = 0; i < enemies.size(); ++i)//update enemies
		enemies[i].update(dt);
}

void World::render(sf::RenderTarget &target)const
{
	renderBackGround(target);
	renderBullets(target);
	renderEntities(target);
}

void World::renderBackGround(sf::RenderTarget & target)const
{
	for (std::size_t i = 0; i < backgrounds.size(); ++i)
		target.draw(backgrounds[i]); //draw background
}

void World::renderBullets(sf::RenderTarget & target)const
{

	for (auto laser : player->getBullets()) //draw player lasers
		laser->draw(target);

	auto enemy = enemies; //TO-DO FIX
	for (std::size_t i = 0; i < enemies.size(); ++i)
	{
		for (std::size_t k = 0; k < enemy[i].getBullets().size(); ++k)
		{
			enemy[i].getBullets()[k]->draw(target);
		}
	}
}

void World::renderEntities(sf::RenderTarget & target)const
{
	for (std::size_t i = 0; i < particles.size(); ++i)
		target.draw(particles[i]);

	for (auto enemy : enemies) //for enemey in enemies draw every enemy
		enemy.draw(target);

	for (auto ast : asteroids)
		ast.draw(target);

	for (auto pick : shieldPickups)
		pick->draw(target);

	for (auto pick : hpPickups)
		pick->draw(target);

	player->draw(target); //draw player

	target.draw(score);
	scoreText->draw(target);
}


void World::logic()
{
	backgroundScrolling();
	collision();
}

void World::collision() //check all collisions
{
	playerCollision();
	enemyCollision();
	windowCollision();
	laserCollision();
}

void World::enemyCollision()
{
	//if enemy laser hits player
	for (std::size_t i = 0; i < enemies.size(); ++i)
	{
		for (std::size_t k = 0; k < enemies[i].getBullets().size(); ++k)
		{
			if (enemies[i].getBullets()[k]->getBullet().getGlobalBounds().intersects(player->getPlayer().getGlobalBounds()))//if enemy bullet collides with player or player shield
			{
				if (player->isAlive())
				{
					player->takeDmg(enemies[i].getDmg());
					enemies[i].getBullets().erase(enemies[i].getBullets().begin() + k); //erase bullet
				}
			}
		}
	}

	for (std::size_t i = 0; i < enemies.size(); ++i)
	{
		for (std::size_t k = 0; k < enemies[i].getBullets().size(); ++k)
		{
			if (player->getSp() > 0.0f) //if shield power is greater than 0
			{
				if (player->getShield() != nullptr) //if we still have a shield
				{
					if (enemies[i].getBullets()[k]->getBullet().getGlobalBounds().intersects(player->getShield()->getShield().getGlobalBounds()))//if enemy bullet collides with player or player shield
					{
						World::sounds[(int)Sound::shieldHit].play();
						player->takeSpDmg(enemies[i].getDmg());
						enemies[i].getBullets().erase(enemies[i].getBullets().begin() + k); //erase bullet
					}
				}
			}
		}
	}
}

void World::playerCollision()
{
	for (std::size_t i = 0; i < enemies.size(); ++i)
	{
		//if player collides with enemy
		if (player->getPlayer().getGlobalBounds().intersects(enemies[i].getEnemy().getGlobalBounds()))
		{
			if (player->isAlive())
			{
				player->takeDmg(enemies[i].getDmg());
			}
		}
	}

	//asteroid collision with player
	for (std::size_t i = 0; i < asteroids.size(); ++i)
	{
		if (player->getPlayer().getGlobalBounds().intersects(asteroids[i].getAsteroid().getGlobalBounds()))
		{
			player->takeDmg(asteroids[i].getDmg());
		}
	}

	//entity collision with player
	for (std::size_t i = 0; i < shieldPickups.size(); ++i)
	{
		if (player->getPlayer().getGlobalBounds().intersects(shieldPickups[i]->getPickup().getGlobalBounds()))
		{
			player->rechargeShield();
			shieldPickups.erase(shieldPickups.begin() + i);
		}
	}
	for (std::size_t i = 0; i < hpPickups.size(); ++i)
	{
		if (player->getPlayer().getGlobalBounds().intersects(hpPickups[i]->getPickup().getGlobalBounds()))
		{
			if(player->isAlive())
				player->increaseHp();

			hpPickups.erase(hpPickups.begin() + i);
		}
	}
}

void World::laserCollision()
{
	//laser collision with asteroids and enemies

	for (std::size_t i = 0; i < enemies.size(); ++i)
	{
		for (std::size_t k = 0; k < player->getBullets().size(); ++k)
		{
			if (player->getBullets()[k]->getBullet().getGlobalBounds().intersects(enemies[i].getEnemy().getGlobalBounds())) //if player bullet hits enemy
			{
				particles.push_back(Particle(sf::Vector2f(enemies[i].getPosition().x - (10 + rand() %50) , enemies[i].getPosition().y - 30.0f), 
					sf::Color(80 ,50, 0, 255), 100));

				enemies[i].takeDmg(player->getDmg());
				player->getBullets().erase(player->getBullets().begin() + k);

				if (!enemies[i].isAlive())
				{
					scorenum++;
					enemies.erase(enemies.begin() + i);
					spawnEnemies(); //spawn new enemy after one is killed
				}

			}
		}
	}

	for (std::size_t i = 0; i < asteroids.size(); ++i)
	{
		for (std::size_t k = 0; k < player->getBullets().size(); ++k)
		{
			if (player->getBullets()[k]->getBullet().getGlobalBounds().intersects(asteroids[i].getAsteroid().getGlobalBounds()))
			{
				particles.push_back(Particle(sf::Vector2f(asteroids[i].getPosition().x  , asteroids[i].getPosition().y), sf::Color(100, 100, 100, 100), 400));

				int ran = randomInt(1, 10);
				if(ran==5)
					shieldPickups.push_back(new ShieldPickup(asteroids[i].getPosition())); //spawn pickup
				if (ran == 1)
					hpPickups.push_back(new HpPickup(asteroids[i].getPosition()));

				asteroids.erase(asteroids.begin() + i);
				spawnAsteroids();
			}
		}
	}
}

void World::windowCollision()
{
	//window collision with player
	if (player->getPlayer().getGlobalBounds().left + 20 < 0 //left
		|| player->getPlayer().getGlobalBounds().top < 0 //top
		|| player->getPlayer().getPosition().y + player->getPlayer().getGlobalBounds().height > Game::window->getSize().y //bottom
		|| player->getPlayer().getGlobalBounds().left + 70 > Game::window->getSize().x) //right
	{
		player->reverseVel();
	}
}

void World::backgroundScrolling()
{
	for (std::size_t i = 0; i < backgrounds.size(); ++i)
	{
		backgrounds[i].move(backgroundDirection);

		if (backgrounds[i].getPosition().y > Game::window->getSize().y)
		{
			backgrounds.erase(backgrounds.begin() + i);
			backgrounds.push_back(background);
		}
	}
	
}

void World::spawnEnemies()
{
	enemies.push_back(Enemy(&textures[(int)Texture::enemy]));
}

void World::spawnAsteroids()
{
	float dirx = randomFloat(0.0f, 0.5f); //random float from 0.0f - 0.2f
	asteroids.push_back(Asteroid(&textures[(int)Texture::asteroid], sf::Vector2f(dirx, 1.0f)));
}

void World::freeObjects() //delete any objects off screen
{
	for (std::size_t i = 0; i < enemies.size(); ++i) //free enemies after leaving window
	{
		if (enemies[i].getPosition().y > Game::window->getSize().y + enemies[i].getEnemy().getGlobalBounds().height)
		{
			enemies.erase(enemies.begin() + i);
			spawnEnemies();
		}
	}

	for (std::size_t i = 0; i < asteroids.size(); ++i) //free asteroids after leaving window and spawn more
	{
		if (asteroids[i].getPosition().y > Game::window->getSize().y + asteroids[i].getAsteroid().getGlobalBounds().height)
		{
			asteroids.erase(asteroids.begin() + i);
			spawnAsteroids();
		}
	}

	//free lasers after leaving window

	for (std::size_t i = 0; i < player->getBullets().size(); i++)
	{
		if (player->getBullets()[i]->getPosition().y < 0)
		{
			player->getBullets().erase(player->getBullets().begin() + i);
		}
	}

	//free enemy lasers
	for (std::size_t i = 0; i < enemies.size(); ++i)
	{
		for (std::size_t k = 0; k < enemies[i].getBullets().size(); ++k)
		{
			if (enemies[i].getBullets()[k]->getPosition().y > Game::window->getSize().y)
			{
				enemies[i].getBullets().erase(enemies[i].getBullets().begin() + k); //delete enemy lasers if off screen
			}
		}
	}

	//free particles
	for (std::size_t i = 0; i < particles.size(); ++i)
	{
		if (particles[i].readyDel())
		{
			particles.erase(particles.begin() + i);
		}
	}

	//free pickups
	for (std::size_t i = 0; i < shieldPickups.size(); ++i)
	{
		if (shieldPickups[i]->getPickup().getPosition().y > Game::window->getSize().y)
		{
			shieldPickups.erase(shieldPickups.begin() + i);
		}
	}
	for (std::size_t i = 0; i < hpPickups.size(); ++i)
	{
		if (hpPickups[i]->getPickup().getPosition().y > Game::window->getSize().y)
		{
			hpPickups.erase(hpPickups.begin() + i);
		}
	}
}
