#include "grid.h"
#include "food.h"

Cell** Grid::m_cells = nullptr;

std::vector <std::pair<Cell*, sf::Vertex*>> Grid::Pheromones;
std::vector <std::pair<Cell*, sf::Vector2i>> Grid::Food;
std::vector <std::pair<Cell*, sf::Vector2i>> Grid::Obstacles;
std::vector <sf::VertexArray> Grid::SmellRadius;
std::vector <void*> Grid::Colonies;
int Grid::m_height = 0;
int Grid::m_width = 0;

Grid::Grid(int width, int height) {
	Grid::m_width = width;
	Grid::m_height = height;
	m_cells = new Cell*[height];
	for (int j = 0; j < height; j++) {
		m_cells[j] = new Cell[width];
		
	}
}

void Grid::clear() {
	for (int i = 0; i < getHeight(); i++) {
		for (int j = 0; j < getWidth(); j++) {
			m_cells[i][j] = {};
		}
	}

	Pheromones.clear();
	Food.clear();
	SmellRadius.clear();
	Obstacles.clear();

}

void Grid::Assign(int i, int j, Cell data, sf::Vector2i position) {
	m_cells[i][j].assign(data, position);
}

void Grid::update() {
	//std::cout << "Ph: " << m_pvertices.size() << std::endl;

	/*auto i = Pheromones.begin();
	while (i != Pheromones.end()) {
		if ((*i).first->attributes.second < Config::PheremoneDecay) {
			(*i).first = {};
			(*i).second.clear();
			i = Pheromones.erase(i);
		}
		else {
			(*i).first->attributes.second -= Config::PheremoneDecay;
			++i;
		}
	}*/
}

void Grid::UpdateSmellRadius() {
	Grid::SmellRadius.clear();

	auto k = Grid::Food.begin();
	while (k != Grid::Food.end()) {
		int r = ((Foodc*)((*k).first->food))->getRadius();
		int i = (*k).second.x;
		int j = (*k).second.y;
		sf::VertexArray va(sf::Quads);

		va.append({ sf::Vector2f(j - r + 1.f, i - r + 1.f), sf::Color(255, 255, 0, 100) });
		va.append({ sf::Vector2f(j + r + 0.f, i - r + 1.f), sf::Color(255, 255, 0, 100) });
		va.append({ sf::Vector2f(j + r + 0.f, i + r + 0.f), sf::Color(255, 255, 0, 100) });
		va.append({ sf::Vector2f(j - r + 1.f, i + r + 0.f), sf::Color(255, 255, 0, 100) });

		Grid::SmellRadius.push_back(va);

		++k;
	}
}

sf::Vector2f Grid::getCenter() {
	return sf::Vector2f(m_width / 2.f, m_height / 2.f);
}

Grid::~Grid() {
	clear();

	for (int i = 0; i < m_height; i++)
		delete[] m_cells[i];
	delete[] m_cells;
}
