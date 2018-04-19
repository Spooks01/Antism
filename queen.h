#pragma once

#include "ant.h"

class Queen : public Ant
{
public:
	Queen() {
		setFillColor(sf::Color::Red);
		setSize(sf::Vector2f(16, 16));
	}
	Queen(sf::Vector2f position) : Ant(position) {
		setPosition(position);

		setFillColor(sf::Color::Red);
		setSize(sf::Vector2f(16, 16));
	}

	void move(sf::Vector2f offset) override {
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

		Grid::GetGrid()[(int)cp.y][(int)cp.x].assign(-4, nullptr, nullptr);
		Grid::GetGrid()[(int)np.y][(int)np.x].assign(-4, this, nullptr);

		setPosition(np);
	}

private:

};

