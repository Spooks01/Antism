#include "colony.h"

Colony::Colony(sf::Vector2f center) {
	m_center = center;
}

void Colony::addAnt(Ant * ant) {
	m_ants.emplace(index++, ant);
}

void Colony::removeAnt(int index) {
	m_ants.erase(index);
}

void Colony::spawnAnt(sf::Vector2f position) {
	m_ants.emplace(index++, new Ant(position));
}

void Colony::spawnAnt() {
	m_ants.emplace(index++, new Ant());
}

void Colony::update() {
	auto i = m_ants.begin();
	while (i != m_ants.end()) {
		i->second->update();

		if ((*i).second->getHealth() > 0)
			++i;
		else
			i = m_ants.erase(i);
	}

	m_queen->update();
	if (m_queen->getStatus()) {
		sf::Vector2f pos = sf::Vector2f(m_center.x, m_center.y + 3);
		Grid::GetGrid()[(int)pos.y][(int)pos.x] = { 1, nullptr };

		m_ants.emplace(index++, new Ant(pos));

		m_queen->setStatus(false);
	}
}

void Colony::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	auto i = m_ants.begin();
	while (i != m_ants.end()) {
		if ((*i).second->getHealth() > 0) {
			target.draw(*(*i).second, states);
			++i;
		}
	}

	target.draw(*m_queen, states);
}

void Colony::generate(int size) {
	clean();

	m_generation = 1;

	m_queen = new Queen(m_center);
	Grid::Assign((int)m_center.y, (int)m_center.x, { -4, m_queen, nullptr });

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
		Grid::Assign((int)pos.y, (int)pos.x, { 1, nullptr });

		m_ants.emplace(index++, new Ant(pos));
	}

}

void Colony::clean() {
	index = 0;

	for (size_t i = 0; i < m_ants.size(); i++) {
		delete m_ants[i];
	}
	m_ants.clear();
}
