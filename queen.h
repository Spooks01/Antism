#pragma once

#include "ant.h"

class Queen : public Ant
{
public:
	Queen() {
		setFillColor(sf::Color::Red);
		setSize(sf::Vector2f(16, 16));
	}
	Queen(sf::Vector2f position) : Ant(position) {
		setPosition(position);

		setFillColor(sf::Color::Red);
		setSize(sf::Vector2f(16, 16));
	}

private:

};

