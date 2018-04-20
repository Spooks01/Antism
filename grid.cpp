#include "grid.h"

Grid::Cell** Grid::m_cells = nullptr;
std::vector<std::pair<Grid::Cell*, sf::Vector2i>> Grid::m_pheromones;
std::vector <std::pair<Grid::Cell*, std::vector<sf::Vertex>>> Grid::m_pvertices;
int Grid::m_height = 0;
int Grid::m_width = 0;

Grid::Grid(int width, int height) {
	Grid::m_width = width;
	Grid::m_height = height;
	m_cells = new Cell*[height];
	for (int j = 0; j < height; j++) {
		m_cells[j] = new Cell[width];
		for (int i = 0; i < width; i++) {

		}
	}
}

void Grid::clearGrid() {
	for (int i = 0; i < getHeight(); i++) {
		for (int j = 0; j < getWidth(); j++) {
			m_cells[i][j] = {};
		}
	}

}

std::vector<std::pair<Grid::Cell*, sf::Vector2i>> Grid::getPheromones() {
	return m_pheromones;
}

void Grid::update() {
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

sf::Vector2f Grid::getCenter() {
	return sf::Vector2f(m_width / 2.f, m_height / 2.f);
}

Grid::~Grid() {
	for (int i = 0; i < m_height; i++)
		delete[] m_cells[i];
	delete[] m_cells;
}
