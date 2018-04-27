#pragma once

#include <vector>
#include <unordered_map>

#include "queen.h"

class Colony : public sf::Drawable
{
public:
	Colony(sf::Vector2f center);

	void addAnt(Ant* ant);
	void removeAnt(int index);

	void spawnAnt(sf::Vector2f position);
	void spawnAnt();

	void update(int frame);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void generate(int size);

	void clean();

	int getAntCount() {
		return m_ants.size();
	}
	void passFrames(int f);
	void depositFood();
	int getStoredFood();

private:
	int index = 0;
	int m_generation = 0;
	int m_frame = 60;
	sf::Vector2f m_center;
	int m_numFrames;
	int m_colonyFood;
	//std::unordered_map<int, Ant*> m_ants;
	std::vector<Ant*> m_ants;
	std::vector<Ant*>::iterator m_iterator;
	Queen* m_queen;
};

