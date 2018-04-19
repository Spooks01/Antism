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
		int x = rand() % 2 + 1;
		int y = rand() % 2 + 1;

		int dx = rand() % 2 + 1;
		int dy = rand() % 2 + 1;

		if (dx == 2)
			x = -x;
		if (dy == 2)
			y = -y;

		move(sf::Vector2f(x, y));
	}

	virtual void move(sf::Vector2f offset) {
		sf::Vector2f cp = getPosition();
		sf::Vector2f np = cp + offset;

		sf::Vector2f limit = sf::Vector2f(Grid::getWidth(), Grid::getHeight());
		if (np.x < 0)
			np.x = cp.x + 1;
		else if (np.x >= limit.x)
			np.x = cp.x - 1;

		if (np.y < 0)
			np.y = cp.y + 1;
		else if (np.y >= limit.y)
			np.y = cp.y - 1;

		setPosition(np);

		Grid::GetGrid()[(int)cp.y][(int)cp.x].assign(-2, nullptr, nullptr, {0, m_pheromone }, sf::Vector2i(cp.x, cp.y) );
		Grid::GetGrid()[(int)cp.y][(int)cp.x].assign(-4, nullptr, nullptr);
		Grid::GetGrid()[(int)np.y][(int)np.x].assign(-4, this, nullptr);
	}

private:
	float m_pheromone = 5.f;
};

