#pragma once

#include <SFML/Graphics.hpp>

#include "grid.h"

class Ant : public sf::RectangleShape
{
public:
	Ant();
	Ant(sf::Vector2f position);
	~Ant();

	void update() {
		move(sf::Vector2f(1, 1));
	}

	void move(sf::Vector2f offset) {
		sf::Vector2f cp = getPosition();
		sf::Vector2f np = cp + offset;

		Grid::GetGrid()[(int)cp.x][(int)cp.y] = { -1, nullptr };
		Grid::GetGrid()[(int)np.x][(int)np.y] = { 1,  nullptr };
	}

private:
	
};

