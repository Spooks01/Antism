#include "button.h"


Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Color fillC) {
	setPosition(position);
	setSize(size);
	setFillColor(fillC);
	color = fillC;
	clicked = false;
}

Button::~Button()
{
}

bool Button::update(sf::Vector2f mousePos)
{
	clicked = false;
	if (mousePos.x > getPosition().x && mousePos.x < getPosition().x + getSize().x && mousePos.y > getPosition().y && mousePos.y < getPosition().y + getSize().y) {
		this->setFillColor(sf::Color::Black);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->setFillColor(color);
			clicked = true;
		}
	}
	else {
		this->setFillColor(color);
	}
	//this->setFillColor(color);
	return clicked;
}
