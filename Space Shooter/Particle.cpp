#include "Particle.h"

Particle::Particle(sf::Vector2f position, sf::Color color, int count)
	:particles(count),vertices(sf::Points, count)
{
	srand(time(NULL));
	this->direction = sf::Vector2f(0.0f, -1.0f);

	this->lifetime = 500.0f;
	for (int i = 0; i < count; i++)
	{
		vertices[i].color = color;
		vertices[i].position = sf::Vector2f(position);
	}
	setEmitter(position);
}

Particle::~Particle()
{

}

void Particle::setEmitter(sf::Vector2f position)
{
	this->position = position;
}

void Particle::update(const float & dt)
{
	for (int i = 0; i < particles.size(); i++)
	{
		particle &p = particles[i];

		float x = randomFloat(-3.0f, 3.0f);
		float y = randomFloat(-10.0f, -5.0f);

		p.velocity=sf::Vector2f(x, y);
		this->lifetime -= 0.1f;


		vertices[i].position += p.velocity * dt;
	}


}

void Particle::draw(sf::RenderTarget & target, sf::RenderStates states)const
{
	states.transform *= getTransform();

	states.texture = nullptr;


	target.draw(vertices, states);
}
