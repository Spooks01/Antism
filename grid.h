#pragma once

#include <vector>
#include <array>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics/Vertex.hpp>

#include "config.h"

class Grid
{
public:
	struct Cell {
		/*
		-4 = Update Ant
		-3 = Update Food
		-2 = Update Attributes
		-1 = Empty
		0  = Food
		1  = Basic Ant
		2  = Queen
		*/
		int id = -1;
		void* ant = nullptr;
		void* food = nullptr;

		// Smell & Pheromone
		std::pair<float, float> attributes = std::make_pair<float, float>(0, 0);

		void assign(Cell cell) {
			if (id != -2) {
				this->id = cell.id;
				this->ant = cell.ant;
				this->food = cell.food;
			}
				
			this->attributes.first += attributes.first;
			this->attributes.second += attributes.second;
		}

		void assign(int id = -1, void* ant = nullptr, void* food = nullptr, std::pair<float, float> attributes = std::make_pair<float, float>(0, 0), sf::Vector2i position = sf::Vector2i()) {
			if (id > -1) {
				this->id = id;
				this->ant = ant;
				this->food = food;
			}
			else if (id == -2) {
				this->attributes.first += attributes.first;
				if (attributes.second > 0) {
					this->attributes.second += attributes.second;

					std::vector<sf::Vertex> quads;

					quads.push_back({sf::Vector2f(position) + sf::Vector2f(0, 0), sf::Color::Cyan});
					quads.push_back({sf::Vector2f(position) + sf::Vector2f(1, 0), sf::Color::Cyan});
					quads.push_back({sf::Vector2f(position) + sf::Vector2f(1, 1), sf::Color::Cyan});
					quads.push_back({sf::Vector2f(position) + sf::Vector2f(0, 1), sf::Color::Cyan});

					Grid::m_pheromones.push_back({ this, position });
					Grid::m_pvertices.push_back({ this, quads });
				}
					
			} else if (id == -3) {
				if (food == nullptr)
					this->id = -1;
				else
					this->id = 0;

				this->food = food;
				this->attributes.first += attributes.first;
			}
			else if (id == -4) {
				if (ant == nullptr)
					this->id = -1;
				else
					this->id = 1;

				this->ant = ant;
			}
		}
	};

public:
	Grid(int width, int height) {
		Grid::m_width = width;
		Grid::m_height = height;
		m_cells = new Cell*[height];
		for (int j = 0; j < height; j++) {
			m_cells[j] = new Cell[width];
			for (int i = 0; i < width; i++) {
				
			}
		}
	}

	void clearGrid() {
		for (int i = 0; i < getHeight(); i++) {
			for (int j = 0; j < getWidth(); j++) {
				m_cells[i][j] = {};
			}
		}
		
	}

	~Grid() {	
		for (int i = 0; i < m_height; i++)
			delete[] m_cells[i];
		delete[] m_cells;
	}

	static Cell** GetGrid() { return m_cells; }
	static std::vector<std::pair<Cell*, sf::Vector2i>> getPheromones() {
		return m_pheromones;
	}

	static int getWidth() { return m_width; }
	static int getHeight() { return m_height; }
	static int getSize() { return m_width * m_height; }

	static void update() {
		//std::cout << "Ph: " << m_pvertices.size() << std::endl;

		auto i = m_pvertices.begin();
		while (i != m_pvertices.end()) {
			if ((*i).first->attributes.second < Config::pheremoneDecay) {
				(*i).first = {};
				(*i).second.clear();
				i = m_pvertices.erase(i);
			}
			else {
				(*i).first->attributes.second -= Config::pheremoneDecay;
				++i;
			}
		}
	}

	sf::Vector2f getCenter() {
		return sf::Vector2f(m_width / 2.f, m_height / 2.f);
	}

public:
	static std::vector <std::pair<Cell*, std::vector<sf::Vertex>>> m_pvertices;

private:
	static Cell** m_cells;
	static std::vector<std::pair<Cell*, sf::Vector2i>> m_pheromones;
	
	static int m_width, m_height;
};