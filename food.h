#pragma once

#include <SFML/Graphics.hpp>

#include "grid.h"

class Food : public sf::RectangleShape 
{
public:
	Food(sf::Vector2f position);

	void spawn();

	int getRadius();

private:
	float m_smell_strength = 100;
	float m_decay = 0.33f;
	int m_radius = 3;
};

