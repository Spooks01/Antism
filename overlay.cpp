#include "overlay.h"

Overlay::Overlay(sf::Font * font) {
	this->setFillColor(sf::Color(255, 255, 255, 64));
	overlayAntCount.setFont(*font);
	overlayAntCount.setCharacterSize(18);
	overlayAntCount.setFillColor(sf::Color::White);
	overlayFoodCount.setFont(*font);
	overlayFoodCount.setCharacterSize(18);
	overlayFoodCount.setFillColor(sf::Color::White);
	div1.setSize(sf::Vector2f(this->getSize().x, 25));
	div1.setFillColor(sf::Color(255, 255, 255, 100));
	pheremoneDecay.setFont(*font);
	pheremoneDecay.setCharacterSize(18);
	pheremoneDecay.setFillColor(sf::Color::White);
	pheremoneDecay.setString("Pheremone decay: " + std::to_string(Config::PheremoneDecay));
	foodSmellRadius.setFont(*font);
	foodSmellRadius.setCharacterSize(18);
	foodSmellRadius.setFillColor(sf::Color::White);
	foodSmellRadius.setString("New food radius: " + std::to_string(Config::FoodSmellRadius));
	buttonLabel.setFont(*font);
	buttonLabel.setCharacterSize(18);
	buttonLabel.setFillColor(sf::Color::White);

}

Overlay::~Overlay()
{
}

void Overlay::updateStats(int nAnt, int nFo) {
	overlayAntCount.setString("Number of ants: " + std::to_string(nAnt));
	overlayFoodCount.setString("Amount of food: " + std::to_string(nFo));
}

void Overlay::updateFieldPh(sf::String nT) {
	pheremoneDecay.setString("Pheremone decay: " + nT);
}

void Overlay::updateFieldFo(sf::String newText) {
	foodSmellRadius.setString("New food radius: " + newText);
}

void Overlay::setUpText() {
	overlayAntCount.setPosition(sf::Vector2f(this->getPosition().x + 30, this->getPosition().y + 25));
	overlayFoodCount.setPosition(sf::Vector2f(this->getPosition().x + 30, this->getPosition().y + 50));
	div1.setPosition(sf::Vector2f(this->getPosition().x, this->getPosition().y + 75));
	pheremoneDecay.setPosition(sf::Vector2f(this->getPosition().x + 30, this->getPosition().y + 100));
	foodSmellRadius.setPosition(sf::Vector2f(this->getPosition().x + 30, this->getPosition().y + 125));
	ovButton = new Button(sf::Vector2f(this->getPosition().x + 10, this->getPosition().y + 150), sf::Vector2f(this->getSize().x - 20, 30), sf::Color(255, 255, 255, 100));
	buttonLabel.setPosition(sf::Vector2f(ovButton->getPosition().x + 70, ovButton->getPosition().y + 5));
	buttonLabel.setString("Save changes");
}

void Overlay::checkTextHover(sf::Vector2f mousePos) {
	if (mousePos.x > pheremoneDecay.getPosition().x && mousePos.x < pheremoneDecay.getPosition().x + pheremoneDecay.getLocalBounds().width
		&& mousePos.y > pheremoneDecay.getPosition().y && mousePos.y < pheremoneDecay.getPosition().y + pheremoneDecay.getLocalBounds().height) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			editMode = 1;
		}
	}
	if (mousePos.x > foodSmellRadius.getPosition().x && mousePos.x < foodSmellRadius.getPosition().x + foodSmellRadius.getLocalBounds().width
		&& mousePos.y > foodSmellRadius.getPosition().y && mousePos.y < foodSmellRadius.getPosition().y + foodSmellRadius.getLocalBounds().height) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			editMode = 2;
		}
	}
	else {
	
	}
}
