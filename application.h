#pragma once

#include <SFML/Graphics.hpp>

#include <cstring>
#include <vector>
#include <fstream>
#include "ant.h"
#include "overlay.h"
#include "timer.h"
#include "grid.h"
#include "colony.h"
#include "food.h"

class Application
{
public:
	Application(int width, int height, bool vS, std::string title);
	~Application();

	void run();
	void update();

	void setup();
	
private:
	enum States { Menu, Run, Pause };
	States state;
	Overlay *m_overlay;
	sf::RenderWindow m_window;
	Grid* m_grid;
	sf::Text m_label, m_tempOverlayLabel, m_paused;
	Fps fps;
	sf::View m_view;
	Colony *m_colony;
	sf::RectangleShape m_bg;
	sf::Font m_font;
	sf::RectangleShape m_logo;
	sf::Texture m_logoTexture;
	bool editingOverlayPh, editingOverlayFo;
};

