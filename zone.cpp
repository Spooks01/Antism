#include "zone.h"


Zone::Zone(int width, int height)
{
	this->setSize(sf::Vector2f(width, height));
}


Zone::~Zone()
{
}


bool Zone::update(sf::Vector2f mousePos) {
	clicked = false;
	if (mousePos.x > this->getGlobalBounds().left && mousePos.x < this->getGlobalBounds().left + this->getGlobalBounds().width
		&& mousePos.y > this->getGlobalBounds().top && mousePos.y < this->getGlobalBounds().top + this->getGlobalBounds().height) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {	
			clicked = true;
		}
		
	}
	return clicked;
}
