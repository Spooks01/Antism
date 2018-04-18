#include "ant.h"

Ant::Ant()
{
	setFillColor(sf::Color::Green);
	setSize(sf::Vector2f(20, 20));
}

Ant::Ant(sf::Vector2f position)
{
	setPosition(position);

	setFillColor(sf::Color::Green);
	setSize(sf::Vector2f(20, 20));
}


Ant::~Ant()
{
}

