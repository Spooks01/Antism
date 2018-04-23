#pragma once
#include <SFML/Graphics.hpp>
class Zone : public sf::RectangleShape
{
public:
	Zone(int width, int height);
	~Zone();
	bool clicked;
	bool update(sf::Vector2f mousePos);;
};

