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

		setPosition(np);

		spawn();

		Grid::GetGrid()[(int)cp.y][(int)cp.x].assign(-3, nullptr, nullptr);
		Grid::GetGrid()[(int)np.y][(int)np.x].assign(-3, nullptr, this);
	}

	void spawn() {
		for (int i = 0; i < m_radius; i++) {
			sf::Vector2i p = sf::Vector2i(getPosition());
			sf::Vector2i limit = sf::Vector2i(Grid::getWidth(), Grid::getHeight());

			if (p.x - i <= i)
				p.x = i;
			if (p.x  + i >= limit.x)
				p.x = limit.x - 1 - i;
			if (p.y - i <= i)
				p.y = i;
			if (p.y + i >= limit.y)
				p.y = limit.y - 1 - i;

			float smell = m_smell_strength * m_decay / i;

			for (int j = p.x - i; j <= p.x + i; j++) {
				for (int k = p.y - i; k <= p.y + i; k++) {
					Grid::GetGrid()[k][j].assign(-2,  nullptr, nullptr, { smell, 0 });
				}

				Grid::GetGrid()[p.y][j].assign(-2,  nullptr, nullptr, { smell, 0 });
			}

			for (int k = p.y - i; k <= p.y + i; k++) {
				for (int j = p.x - i; j <= p.x + i; j++) {
					Grid::GetGrid()[k][j].assign(-2,  nullptr, nullptr, { smell, 0 });
				} 
				Grid::GetGrid()[k][p.x].assign(-2,  nullptr, nullptr, { smell, 0 });
			}
		}

	}

	int getRadius() { return m_radius; }

private:
	float m_smell_strength = 100;
	float m_decay = 0.33;
	int m_radius = 20;
};

