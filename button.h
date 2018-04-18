#pragma once
#include <SFML/Graphics.hpp>
class Button : public sf::RectangleShape
{
private:
	bool clicked;
public:
	Button(sf::Vector2f position, sf::Vector2f size) {
		setPosition(position);
		setSize(size);
		setFillColor(sf::Color::Blue);
		clicked = false;
	};
	~Button();
	bool update(sf::Vector2f mousePos)
	{
		clicked = false;
		if (mousePos.x > getPosition().x && mousePos.x < getPosition().x + getSize().x && mousePos.y > getPosition().y && mousePos.y < getPosition().y + getSize().y) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				clicked = true;
			}
		}

		return clicked;
	};

};

