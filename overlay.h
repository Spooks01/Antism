#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Config.h"
#include "button.h"
class Overlay : public sf::RectangleShape
{
public:
	Overlay(sf::Font *font, int *w, int *h);
	~Overlay();

	void updateStats(int nAnt, int nFo, int nFc);
	void updateFieldPh(std::string nT);
	void updateFieldFo(std::string newText);
	void updateFieldA(std::string nT);
	void updateFieldB(std::string nT);
	void setUpText();
	
	void checkTextHover(sf::Vector2f mousePos);

public:
	int editMode = 0;
	//stats
	sf::Text overlayAntCount;
	sf::Text overlayQueenCount;
	sf::Text overlayFoodInColony;
	sf::Text overlayFoodCount;
	sf::Text simSpeed;
	//Divider
	sf::RectangleShape div1;
	//editable
	sf::Text pheremoneDecay;
	sf::Text foodSmellRadius;
	sf::Text alpha;
	sf::Text beta;
	//save edited fields
	sf::Text buttonLabel, defaultsLabel;
	Button *ovButton;
	Button *loadDefaults;
	//filewrite
	std::string temp;
};


