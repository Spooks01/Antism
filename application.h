#pragma once

#include <SFML/Graphics.hpp>

#include <cstring>
#include <vector>

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
	void renderHUD();
	void renderAnts();
private:
	sf::RenderWindow m_window;
	Overlay m_overlay;
	std::vector<Ant *> m_ants;
	Grid* m_grid;
	sf::Text m_label;
	Fps fps;
	sf::View m_view;
};

