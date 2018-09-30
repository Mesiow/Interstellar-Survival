#pragma once
#include <SFML/Graphics.hpp>
#include "Utils.h"

class Particle : public sf::Drawable , public sf::Transformable
{
public:
	Particle(sf::Vector2f position, sf::Color color, int count);
	~Particle();

public:
	void update(const float &dt);
	void move(const float &dt);
	void setEmitter(sf::Vector2f position);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;

public:
	inline bool readyDel()const { return this->lifetime <= 0.0f; }

private:
	struct particle
	{
		sf::Vector2f velocity;
		float lifeTime;
	};

private:
	sf::Vector2f position;
	sf::Vector2f direction;

	std::vector<particle> particles;
	sf::VertexArray vertices;

private:
	float lifetime;
	
};