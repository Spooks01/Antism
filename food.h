#pragma once

#include <SFML/Graphics.hpp>

#include "grid.h"

class Food : public sf::RectangleShape 
{
public:
	Food() {
		setFillColor(sf::Color::Magenta);
		setSize(sf::Vector2f(4, 4));
	}

	Food(sf::Vector2f position) {
		setFillColor(sf::Color::Magenta);
		setSize(sf::Vector2f(4, 4));

		move(position);
	}

	void move(sf::Vector2f offset) {
		sf::Vector2f cp = getPosition();
		sf::Vector2f np = cp + offset;

		sf::Vector2f limit = sf::Vector2f(Grid::getWidth(), Grid::getHeight());
		if (np.x < 0)
			np.x = cp.x;
		else if (np.x >= limit.x)
			np.x = cp.x;

		if (np.y < 0)
			np.y = cp.y;
		else if (np.y >= limit.y)
			np.y = cp.y;

		Grid::GetGrid()[(int)cp.y][(int)cp.x] = { -1, nullptr };
		Grid::GetGrid()[(int)np.y][(int)np.x] = { 0,  nullptr };

		setPosition(np);
	}
};

