#include "button.h"


Button::Button(sf::Vector2f position, sf::Vector2f size) {
	setPosition(position);
	setSize(size);
	setFillColor(sf::Color(100, 100, 100, 255));
	clicked = false;
}

Button::~Button()
{
}

bool Button::update(sf::Vector2f mousePos)
{
	clicked = false;
	if (mousePos.x > getPosition().x && mousePos.x < getPosition().x + getSize().x && mousePos.y > getPosition().y && mousePos.y < getPosition().y + getSize().y) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			clicked = true;
		}
	}

	return clicked;
}
