#pragma once

#include <vector>
#include <unordered_map>

#include "queen.h"

class Colony : public sf::Drawable
{
public:
	Colony(sf::Vector2f center) {
		m_center = center;
	}

	void addAnt(Ant* ant) {
		m_ants.emplace(index++, ant);
	}

	void removeAnt(int index) {
		m_ants.erase(index);
	}
	
	void spawnAnt(sf::Vector2f position) {
		m_ants.emplace(index++, new Ant(position));
	}

	void spawnAnt() {
		m_ants.emplace(index++, new Ant());
	}

	void update() {
		for (int i = 0; i < m_ants.size(); ++i)
			m_ants.at(i)->update();
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (int i = 0; i < m_ants.size(); ++i)
			target.draw(*m_ants.at(i), states);
	}

	void generate(int size) {
		clean();

		m_ants.emplace(index++, new Queen(m_center));
		Grid::GetGrid()[(int)m_center.y][(int)m_center.x] = { 2, nullptr };

		for (int i = 0; i < size; ++i) {
			int x = rand() % 100 + 1;
			int y = rand() % 100 + 1;

			int dx = rand() % 2 + 1;
			int dy = rand() % 2 + 1;

			if (dx == 2)
				x = -x;
			if (dy == 2)
				y = -y;

			sf::Vector2f pos = sf::Vector2f(m_center.x + x, m_center.y + y);
			Grid::GetGrid()[(int)pos.y][(int)pos.x] = { 1, nullptr };

			m_ants.emplace(index++, new Ant(pos));
		}
			
	}

	void clean() {
		index = 0;
		
		for (int i = 0; i < m_ants.size(); i++) {
			delete m_ants[i];
		}
		m_ants.clear();
	}

	int getAntCount() {
		return m_ants.size();
	}
private:
	int index = 0;
	sf::Vector2f m_center;

	std::unordered_map<int, Ant*> m_ants;
};

