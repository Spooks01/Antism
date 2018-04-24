#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Config.h"
#include "button.h"
class Overlay : public sf::RectangleShape
{
public:
	Overlay(sf::Font *font, int *w, int *h);;
	~Overlay();

	void updateStats(int nAnt, int nFo);;
	void updateFieldPh(sf::String nT);
	void updateFieldFo(sf::String nT);
	void setUpText();
	
	void checkTextHover(sf::Vector2f mousePos);

public:
	int editMode = 0;
	//stats
	sf::Text overlayAntCount;
	sf::Text overlayQueenCount;
	sf::Text overlayFoodCount;
	//Divider
	sf::RectangleShape div1;
	//editable
	sf::Text pheremoneDecay;
	sf::Text foodSmellRadius;
	//save edited fields
	sf::Text buttonLabel;
	Button *ovButton;
	//filewrite
	std::string temp;
};


