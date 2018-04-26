#pragma once
#include <SFML/Graphics.hpp>
class Zone : public sf::RectangleShape
{
public:
	Zone(int width, int height);
	~Zone();
	const int leftClicked = 1;
	const int rightClicked = 0;
	int update(sf::Vector2f mousePos);
};

