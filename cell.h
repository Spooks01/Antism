#pragma once

#include <vector>
#include <array>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Cell
{
public:
	/*
	-4 = Update Ant
	-3 = Update Food
	-2 = Update Attributes
	-1 = Empty
	0  = Food
	1  = Basic Ant
	2  = Queen
	3  = Obstacle
	*/
	int id = -1;
	void* ant = nullptr;
	void* food = nullptr;
	// Smell & Pheromone
	std::pair<float, float> attributes = std::make_pair<float, float>(0, 0);
	void* obstacle = nullptr;

	inline void assign(Cell cell, sf::Vector2i position = sf::Vector2i()) { assign(cell.id, cell.ant, cell.food, cell.attributes, position, cell.obstacle); }
	void assign(int id = -1, void* ant = nullptr, void* food = nullptr, std::pair<float, float> attributes = std::make_pair<float, float>(0, 0), sf::Vector2i position = sf::Vector2i(), void *obstacle = nullptr);
};

