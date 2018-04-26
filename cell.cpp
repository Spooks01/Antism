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
		this->attributes.first += attributes.first;
	}
	else if (id == -4) {
		if (ant == nullptr)
			this->id = -1;
		else
			this->id = 1;

		this->ant = ant;
	}
	
	this->attributes.first += attributes.first;
	this->attributes.second += attributes.second;

	if (id == -5) {
		this->id = -1;
		this->ant = nullptr;
		this->food = nullptr;
		this->attributes.first = 0;
		this->attributes.second = 0;
	}

	if (id == -6) {
		if (obstacle == nullptr)
			this->id = -1;
		else {
			this->id = 3;

			Grid::Obstacles.push_back({ this, position });
		}
		this->obstacle = obstacle;
	}

}
