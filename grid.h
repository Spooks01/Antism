#pragma once

#include <vector>
#include <array>

class Grid
{
public:
	struct Cell {
		int id;
		int p_str;
		int s_str;
	};

public:
	Grid(int width, int height) {
		m_cells = new int*[height];
		for (int i = 0; i < height; i++)
			m_cells[i] = new int[width];

		m_width = width;
		m_height = height;
	}
	~Grid() {
		
		for (int i = 0; i < m_height; i++)
			delete[] m_cells[i];
		delete[] m_cells;
	}

private:
	int** m_cells;
	int m_width, m_height;
};