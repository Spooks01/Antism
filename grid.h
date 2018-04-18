#pragma once

#include <vector>
#include <array>

#include <SFML/System.hpp>

class Grid
{
public:
	struct Cell {
		/*
		-1 = Empty
		0  = Food
		1  = Basic Ant
		2  = Queen
		*/
		int id;
		void* data;
	};

public:
	Grid(int width, int height) {
		Grid::m_width = width;
		Grid::m_height = height;
		m_cells = new Cell*[height];
		for (int j = 0; j < height; j++) {
			m_cells[j] = new Cell[width];
			for (int i = 0; i < width; i++) {
				m_cells[j][i].id = -1;
				m_cells[j][i].data = nullptr;
			}
			
		}
	}

	~Grid() {	
		for (int i = 0; i < m_height; i++)
			delete[] m_cells[i];
		delete[] m_cells;
	}

	static Cell** GetGrid() { return m_cells; }

	static int getWidth() { return m_width; }
	static int getHeight() { return m_height; }
	static int getSize() { return m_width * m_height; }

	static void UpdateCell(int index, Cell* data) {
		m_cells[index] = data;
	}

	sf::Vector2f getCenter() {
		return sf::Vector2f(m_width / 2.f, m_height / 2.f);
	}


private:
	static Cell** m_cells;
	static int m_width, m_height;
};