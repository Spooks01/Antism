#pragma once
#include <SFML/Graphics.hpp>
#include "grid.h"
class Obstacle : public sf::RectangleShape
{
public:
	Obstacle(sf::Vector2f position);
	~Obstacle();
};

