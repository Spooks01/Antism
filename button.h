#pragma once
#include <SFML/Graphics.hpp>
class Button : public sf::RectangleShape
{
private:
	bool clicked;
	sf::Color color;
public:
	Button(sf::Vector2f position, sf::Vector2f size, sf::Color fillC);;
	~Button();

	bool update(sf::Vector2f mousePos);;
};

