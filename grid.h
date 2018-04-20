#pragma once

#include <vector>
#include <array>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics/Vertex.hpp>

#include "config.h"
#include "cell.h"

class Grid
{
public:
	Grid(int width, int height);
	~Grid();

	void clear();

	static Cell** GetGrid() { return m_cells; }
	static void Assign(int i, int j, Cell data, sf::Vector2i position = sf::Vector2i());
	//static std::vector<std::pair<Cell*, sf::Vector2i>> getPheromones();

	static int getWidth() { return m_width; }
	static int getHeight() { return m_height; }
	static sf::Vector2i GetSize() {
		return { m_width, m_height };
	}
	static void update();

	sf::Vector2f getCenter();

public:
	static std::vector <std::pair<Cell*, std::vector<sf::Vertex>>> Pheromones;
	static std::vector <std::pair<Cell*, sf::Vector2i>> Food;
	static std::vector <void*> Colonies;
	static std::vector <std::pair<int, std::vector<sf::Vertex>>> Pheromones2;
private:
	static Cell** m_cells;
	
	static int m_width, m_height;
};