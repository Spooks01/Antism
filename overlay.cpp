#include "overlay.h"

Overlay::Overlay(sf::Font * font) {
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
	pheremoneDecay.setString("Pheremone decay: " + std::to_string(Config::PheremoneDecay));
}

Overlay::~Overlay()
{
}

void Overlay::updateStats(int nAnt, int nFo) {
	overlayAntCount.setString("Number of ants: " + std::to_string(nAnt));
	overlayFoodCount.setString("Amount of food: " + std::to_string(nFo));
}

void Overlay::updateField(sf::String nT) {
	pheremoneDecay.setString("Pheremone decay: " + nT);
}

void Overlay::setUpText() {
	overlayAntCount.setPosition(sf::Vector2f(this->getPosition().x + 30, this->getPosition().y + 75));
	overlayFoodCount.setPosition(sf::Vector2f(this->getPosition().x + 30, this->getPosition().y + 100));
	pheremoneDecay.setPosition(sf::Vector2f(this->getPosition().x + 30, this->getPosition().y + 125));
}

void Overlay::checkTextHover(sf::Vector2f mousePos) {
	if (mousePos.x > pheremoneDecay.getPosition().x && mousePos.x < pheremoneDecay.getPosition().x + pheremoneDecay.getLocalBounds().width
		&& mousePos.y > pheremoneDecay.getPosition().y && mousePos.y < pheremoneDecay.getPosition().y + pheremoneDecay.getLocalBounds().height) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			editMode = 1;
		}
	}
	else {

	}
}
