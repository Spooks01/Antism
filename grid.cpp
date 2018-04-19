#include "grid.h"

Grid::Cell** Grid::m_cells = nullptr;
std::vector<std::pair<Grid::Cell*, sf::Vector2i>> Grid::m_pheromones;
int Grid::m_height = 0;
int Grid::m_width = 0;