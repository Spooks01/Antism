#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Config.h"
class Overlay : public sf::RectangleShape
{
public:
	Overlay(sf::Font *font) {
		setFillColor(sf::Color(255, 255, 255, 64));
		setSize(sf::Vector2f(400, 300));
		overlayAntCount.setFont(*font);
		overlayAntCount.setCharacterSize(18);
		overlayAntCount.setFillColor(sf::Color::White);
		overlayFoodCount.setFont(*font);
		overlayFoodCount.setCharacterSize(18);
		overlayFoodCount.setFillColor(sf::Color::White);
		pheremoneDecay.setFont(*font);
		pheremoneDecay.setCharacterSize(18);
		pheremoneDecay.setFillColor(sf::Color::White);
		pheremoneDecay.setString("Pheremone decay: " + std::to_string(Config::pheremoneDecay));
	};
	~Overlay();
	void updateStats(int nAnt, int nFo) {
		overlayAntCount.setString("Number of ants: " + std::to_string(nAnt));
		overlayFoodCount.setString("Amount of food: " + std::to_string(nFo));
	};

	void updateField(sf::String nT) {
		pheremoneDecay.setString("Pheremone decay:" + nT);
	}

	void setUpText() {
		overlayAntCount.setPosition(sf::Vector2f(this->getPosition().x + 30, this->getPosition().y + 75));
		overlayFoodCount.setPosition(sf::Vector2f(this->getPosition().x + 30, this->getPosition().y + 100));
		pheremoneDecay.setPosition(sf::Vector2f(this->getPosition().x + 30, this->getPosition().y + 125));
	}
	int editMode = 0;
	void checkTextHover(sf::Vector2f mousePos) {
		if (mousePos.x > pheremoneDecay.getPosition().x && mousePos.x < pheremoneDecay.getPosition().x + pheremoneDecay.getLocalBounds().width
			&& mousePos.y > pheremoneDecay.getPosition().y && mousePos.y < pheremoneDecay.getPosition().y + pheremoneDecay.getLocalBounds().height) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				editMode = 1;
			}
		}
		else {
			
		}
	}
	//stats
	sf::Text overlayAntCount;
	sf::Text overlayQueenCount;
	sf::Text overlayFoodCount;
	//editable
	sf::Text pheremoneDecay;

	//filewrite
	std::string temp;
};


