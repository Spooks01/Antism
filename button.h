#pragma once
#include <SFML/Graphics.hpp>
class Button : public sf::RectangleShape
{
private:
	bool clicked;
public:
	Button(sf::Vector2f position, sf::Vector2f size);;
	~Button();

	bool update(sf::Vector2f mousePos);;
};

