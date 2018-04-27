#pragma once

#include <SFML/Graphics.hpp>

#include "grid.h"

#include <deque>

class Ant : public sf::Drawable
{
public:
	Ant();
	Ant(sf::Vector2f position);
	~Ant();

	virtual void update();
	virtual void getFood();
	virtual void goHome();
	virtual void move(sf::Vector2f offset);
	virtual void setPosition(sf::Vector2f position);
	virtual sf::Vector2f getPosition() { return { m_vertices[0].position.x, m_vertices[0].position.y }; }
	virtual bool getStatus() { return alive; }
	virtual bool isDeleteSafe() { return (m_trail.size() == 0 && !alive); }

	float getHealth();
	std::vector<sf::Vertex>* getTrail() { return &m_pvertices; }
	std::deque<sf::Vector2i>* getTTrail() { return &m_trail; }
	sf::Vertex* getVertices() { return m_vertices; }

protected:
	float m_pheromone = 1.f;
	float m_decay = 0.25f;

	//float m_decay = 1.f;

	float m_identifier = 100.f;
	float m_health = 100;
	float alpha = Config::AlphaParam; // alpha parameter
	float beta = Config::BetaParam; // beta parameter
	bool hasFood = false; 
	bool alive = true;
	std::deque<sf::Vector2i> m_trail;
	std::deque<sf::Vector2f> m_trailoff;
	std::vector<sf::Vertex> m_pvertices;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	virtual void setBlanc();

	int m_size = 1;
	sf::Vertex m_vertices[4];
};

