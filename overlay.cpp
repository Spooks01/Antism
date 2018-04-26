#include "overlay.h"
#include <iostream>

Overlay::Overlay(sf::Font * font, int *w, int *h) {
	this->setFillColor(sf::Color(255, 255, 255, 64));
	this->setSize(sf::Vector2f(*w / 4, *h));
	this->setPosition(*w - *w / 4, 0);
	overlayAntCount.setFont(*font);
	overlayAntCount.setCharacterSize(18);
	overlayAntCount.setFillColor(sf::Color::White);
	overlayFoodCount.setFont(*font);
	overlayFoodCount.setCharacterSize(18);
	overlayFoodCount.setFillColor(sf::Color::White);
	simSpeed.setFont(*font);
	simSpeed.setCharacterSize(18);
	simSpeed.setFillColor(sf::Color::White);
	div1.setSize(sf::Vector2f(this->getSize().x, 25));
	div1.setFillColor(sf::Color(255, 255, 255, 100));
	pheremoneDecay.setFont(*font);
	pheremoneDecay.setCharacterSize(18);
	pheremoneDecay.setFillColor(sf::Color::White);
	std::string temp = std::to_string(Config::PheremoneDecay);
	temp.erase(temp.find_last_not_of('0') + 1, std::string::npos);
	pheremoneDecay.setString("Pheremone decay: " + temp);
	foodSmellRadius.setFont(*font);
	foodSmellRadius.setCharacterSize(18);
	foodSmellRadius.setFillColor(sf::Color::White);
	temp = std::to_string(Config::FoodSmellRadius);
	temp.erase(temp.find_last_not_of('0') + 2, std::string::npos);
	foodSmellRadius.setString("New food radius: " + temp);
	buttonLabel.setFont(*font);
	buttonLabel.setCharacterSize(18);
	buttonLabel.setFillColor(sf::Color::White);
	this->setUpText();
}

Overlay::~Overlay()
{
}

void Overlay::updateStats(int nAnt, int nFo) {
	overlayAntCount.setString("Number of ants: " + std::to_string(nAnt));
	overlayFoodCount.setString("Amount of food: " + std::to_string(nFo));
	if (Config::SimSpeed == 1) {
		simSpeed.setString("Simulation speed: Full");
	}
	else {
		simSpeed.setString("Simulation speed: Half");
	}
}

void Overlay::updateFieldPh(std::string nT) {
	nT.erase(nT.find_last_not_of('0') + 1, std::string::npos);
	pheremoneDecay.setString("Pheremone decay: " + nT);
}

void Overlay::updateFieldFo(std::string newText) {
	newText.erase(newText.find_last_not_of('0') + 2, std::string::npos);
	foodSmellRadius.setString("New food radius: " + newText);
}

void Overlay::setUpText() {
	overlayAntCount.setPosition(sf::Vector2f(this->getPosition().x + this->getSize().x*0.1, this->getPosition().y + 25));
	overlayFoodCount.setPosition(sf::Vector2f(this->getPosition().x + this->getSize().x*0.1, this->getPosition().y + 50));
	simSpeed.setPosition(sf::Vector2f(this->getPosition().x + this->getSize().x*0.1, this->getPosition().y + 75));
	div1.setPosition(sf::Vector2f(this->getPosition().x, this->getPosition().y + 100));
	pheremoneDecay.setPosition(sf::Vector2f(this->getPosition().x + this->getSize().x*0.1, this->getPosition().y + 125));
	foodSmellRadius.setPosition(sf::Vector2f(this->getPosition().x + this->getSize().x*0.1, this->getPosition().y + 150));
	ovButton = new Button(sf::Vector2f(this->getPosition().x + this->getSize().x*0.1, this->getPosition().y + 175), sf::Vector2f(this->getGlobalBounds().width - this->getGlobalBounds().width*0.2, 30), sf::Color(255, 255, 255, 100));
	buttonLabel.setPosition(sf::Vector2f(ovButton->getPosition().x + ovButton->getLocalBounds().width*0.35, ovButton->getPosition().y + 18/4));
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
