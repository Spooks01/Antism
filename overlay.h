#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Config.h"
class Overlay : public sf::RectangleShape
{
public:
	Overlay(sf::Font *font);;
	~Overlay();

	void updateStats(int nAnt, int nFo);;
	void updateField(sf::String nT);

	void setUpText();
	
	void checkTextHover(sf::Vector2f mousePos);

public:
	int editMode = 0;
	//stats
	sf::Text overlayAntCount;
	sf::Text overlayQueenCount;
	sf::Text overlayFoodCount;
	//editable
	sf::Text pheremoneDecay;

	//filewrite
	std::string temp;
};


