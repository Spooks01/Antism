#pragma once

#include <vector>
#include <array>

#include <SFML/System.hpp>

class Grid
{
public:
	struct Cell {
		int id;
		void* data;
	};

public:
	Grid(int width, int height) : m_width(width), m_height(height) {
		m_cells = new Cell*[height];
		for (int i = 0; i < height; i++) {
			m_cells[i] = new Cell[width];
			m_cells[i]->id = -1;
			m_cells[i]->data = nullptr;
		}
	}

	~Grid() {	
		for (int i = 0; i < m_height; i++)
			delete[] m_cells[i];
		delete[] m_cells;
	}

	static Cell** GetGrid() { return m_cells; }

	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	int getSize() { return m_width * m_height; }

	static void UpdateCell(int index, Cell* data) {
		m_cells[index] = data;
	}

	sf::Vector2f getCenter() {
		return sf::Vector2f(m_width / 2.f, m_height / 2.f);
	}

private:
	static Cell** m_cells;
	int m_width, m_height;
};