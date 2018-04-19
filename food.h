#pragma once

#include <SFML/Graphics.hpp>

#include "grid.h"

class Food : public sf::RectangleShape 
{
public:
	Food(sf::Vector2f position) {
		setFillColor(sf::Color::Magenta);
		setSize(sf::Vector2f(4, 4));

		sf::Vector2f cp = getPosition();
		sf::Vector2f np = position;

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
		Grid::GetGrid()[(int)np.y][(int)np.x] = { 0,  this };

		setPosition(np);
		spawn();
	}

	void spawn() {
		for (int i = 1; i <= m_radius; i++) {
			sf::Vector2i p = sf::Vector2i(getPosition());
			sf::Vector2i limit = sf::Vector2i(Grid::getWidth(), Grid::getHeight());

			float smell = m_smell_strength * m_decay / i;

			if (p.x >= i)
				Grid::GetGrid()[p.y][p.x - i].assign({ -2,  nullptr, {smell, 0} });
			if (p.x < limit.x - i)
				Grid::GetGrid()[p.y][p.x + i].assign({ -2,  nullptr, {smell, 0} });
			if (p.y >= i)
				Grid::GetGrid()[p.y - i][p.x].assign({ -2,  nullptr,{ smell, 0 } });
			if (p.y < limit.y - i)
				Grid::GetGrid()[p.y + i][p.x].assign({ -2,  nullptr,{ smell, 0 } });

			if (p.x >= i && p.y >= i)
				Grid::GetGrid()[p.y - i][p.x - i].assign({ -2,  nullptr,{ smell, 0 } });
			if (p.x >= i && p.y < limit.y - i)
				Grid::GetGrid()[p.y + i][p.x - i].assign({ -2,  nullptr,{ smell, 0 } });
			if (p.x < limit.x - i && p.y < limit.y - i)
				Grid::GetGrid()[p.y + i][p.x + i].assign({ -2,  nullptr,{ smell, 0 } });
			if (p.x < limit.x - i && p.y >= i )
				Grid::GetGrid()[p.y - i][p.x + i].assign({ -2,  nullptr,{ smell, 0 } });
		}

	}

private:
	float m_smell_strength = 100;
	float m_decay = 0.33;
	int m_radius = 4;
};

