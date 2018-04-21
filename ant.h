#pragma once

#include <SFML/Graphics.hpp>

#include "grid.h"

#include <deque>

class Ant : public sf::RectangleShape
{
public:
	Ant();
	Ant(sf::Vector2f position);
	~Ant();

	virtual void update(int frame);
	virtual void move(sf::Vector2f offset);

	float getHealth();
	std::deque<sf::Vector2i> getTrail();
	std::vector<sf::Vertex> getVertices() { return m_pvertices; }

protected:
	float m_pheromone = 100.f;
	float m_identifier = 100.f;
	float m_health = 1500;
	std::deque<sf::Vector2i> m_trail;
	std::vector<sf::Vertex> m_pvertices;
};

