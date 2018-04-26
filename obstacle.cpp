#include "obstacle.h"



Obstacle::Obstacle(sf::Vector2f position)
{
	setFillColor(sf::Color::Yellow);
	setSize(sf::Vector2f(1, 1));
	sf::Vector2f cp = getPosition();
	sf::Vector2f np = position;

	sf::Vector2i limit = Grid::GetSize();
	if (np.x < 0)
		np.x = cp.x;
	else if (np.x >= limit.x)
		np.x = cp.x;

	if (np.y < 0)
		np.y = cp.y;
	else if (np.y >= limit.y)
		np.y = cp.y;

	setPosition(np);
	Grid::Assign((int)np.y, (int)np.x, { 3, nullptr, nullptr, { 0.f, 0.f }, this }, sf::Vector2i(np.y, np.x));
}


Obstacle::~Obstacle()
{
	
}

