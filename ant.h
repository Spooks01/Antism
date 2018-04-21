#pragma once

#include <SFML/Graphics.hpp>

#include "grid.h"

class Ant : public sf::RectangleShape
{
public:
	Ant();
	Ant(sf::Vector2f position);
	~Ant();

	virtual void update();
	virtual void move(sf::Vector2f offset);

	float getHealth();

protected:
	float m_pheromone = 100.f;
	float m_health = 1500;
};

