#pragma once

#include <SFML/Graphics.hpp>

class Overlay : public sf::RectangleShape
{
public:
	Overlay(sf::Font *font) {
		setFillColor(sf::Color(255, 255, 255, 64));
		setSize(sf::Vector2f(400, 300));
		overlayText1.setFont(*font);
		overlayText1.setCharacterSize(18);
		overlayText1.setFillColor(sf::Color::White);
		
	};
	~Overlay();
	void update(int n) {
		overlayText1.setString("Number of ants: " + std::to_string(n));
	};

	void setUpText() {
		overlayText1.setPosition(sf::Vector2f(this->getPosition().x + 30, this->getPosition().y + 75));
	}
	sf::Text overlayText1;
};


