#pragma once

#include <SFML/Graphics.hpp>

#include "grid.h"



class Food : public sf::RectangleShape 
{
public:
	Food(sf::Vector2f position);

	void spawn();

	int getRadius();
	int getCapacity() { return m_capacity; }
	
	void despawn();
	void lowerCapacity() { m_capacity--; }

private:
	int m_capacity = Config::FoodCapacity;
	float m_smell_strength = 100;
	float m_decay = 0.33f;
	int m_radius = Config::FoodSmellRadius;
};

typedef Food Foodc;