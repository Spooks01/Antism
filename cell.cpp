#include "cell.h"

#include "grid.h"

void Cell::assign(int id, void * ant, void * food, std::pair<float, float> attributes, sf::Vector2i position, void *obstacle) {
	if (id > -1) {
		this->id = id;
		this->ant = ant;
		this->food = food;
	}
	else if (id == -2) {


	}
	else if (id == -3) {
		if (food == nullptr)
			this->id = -1;
		else {
			this->id = 0;
		
			Grid::Food.push_back({ this, position });
		}
			

		this->food = food;
		//this->attributes.first += attributes.first;
	}
	else if (id == -4) {
		if (ant == nullptr)
			this->id = -1;
		else
			this->id = 1;

		this->ant = ant;

		if (attributes.second > 0) {
			/*sf::Vertex vertices[4];

			vertices[0] = { sf::Vector2f(position.x, position.y) + sf::Vector2f(0, 0), sf::Color::Cyan };
			vertices[1] = { sf::Vector2f(position.x, position.y) + sf::Vector2f(1, 0), sf::Color::Cyan };
			vertices[2] = { sf::Vector2f(position.x, position.y) + sf::Vector2f(1, 1), sf::Color::Cyan };
			vertices[3] = { sf::Vector2f(position.x, position.y) + sf::Vector2f(0, 1), sf::Color::Cyan };

			Grid::Pheromones.push_back({ this, vertices });*/
		}
	}
	if (this->attributes.first < Config::MaxSmell)
		this->attributes.first += attributes.first;
	if (this->attributes.second < Config::MaxPheromone)
		this->attributes.second += attributes.second;

	if (id == -5) {
		this->id = -1;
		this->ant = nullptr;
		this->food = nullptr;
		this->attributes.first = 0;
		this->attributes.second = 0;
	}

	if (id == -6) {
		if (obstacle == nullptr) {
			this->id = -1;
			std::cout << "nullptr" << std::endl;
		}
		else {
			this->id = 3;
			Grid::Obstacles.push_back({ this, position });
		}
		this->obstacle = obstacle;
	}
	
}
