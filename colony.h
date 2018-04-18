#pragma once

#include <vector>
#include <unordered_map>

#include "ant.h"

class Colony : public sf::Drawable, public sf::Transformable
{
public:
	Colony(sf::Vector2f center) {
	}

	void addAnt(Ant* ant) {
		m_ants.emplace(index++, ant);
	}

	void removeAnt(int index) {
		m_ants.erase(index);
	}
	
	void spawnAnt(sf::Vector2f position = sf::Vector2f()) {
		m_ants.emplace(index++, new Ant(position));
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (int i = 0; i < m_ants.size(); ++i)
			target.draw(*m_ants.at(i), states);
	}


private:
	int index = 0;
	sf::Vector2f m_center;
	//std::vector<Ant*> m_ants;
	std::unordered_map<int, Ant*> m_ants;
};

