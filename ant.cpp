#include "ant.h"

Ant::Ant()
{
	setFillColor(sf::Color::Green);
	setSize(sf::Vector2f(1, 1));

	m_health = float(rand() % 1500 + 1000);
}

Ant::Ant(sf::Vector2f position)
{
	setPosition(position);

	setFillColor(sf::Color::Green);
	setSize(sf::Vector2f(1, 1));

	m_health = float(rand() % 1500 + 1000);
}


Ant::~Ant()
{
}

void Ant::update() {
	float x = (float)(rand() % 1 + 1);
	float y = (float)(rand() % 1 + 1);

	int dx = rand() % 2 + 1;
	int dy = rand() % 2 + 1;

	if (dx == 2)
		x = -x;
	if (dy == 2)
		y = -y;

	move(sf::Vector2f((float)x, (float)y));
	m_health--;
}

float Ant::getHealth() {
	return m_health;
}

void Ant::move(sf::Vector2f offset) {
	sf::Vector2f cp = getPosition();
	sf::Vector2f np = cp + offset;

	sf::Vector2f limit = sf::Vector2f((float)Grid::getWidth(), (float)Grid::getHeight());
	if (np.x < 0)
		np.x = cp.x + 1;
	else if (np.x >= limit.x)
		np.x = cp.x - 1;

	if (np.y < 0)
		np.y = cp.y + 1;
	else if (np.y >= limit.y)
		np.y = cp.y - 1;

	setPosition(np);

	Grid::GetGrid()[(int)cp.y][(int)cp.x].assign(-2, nullptr, nullptr, { 0.f, m_pheromone }, sf::Vector2i((int)cp.x, (int)cp.y));
	Grid::GetGrid()[(int)cp.y][(int)cp.x].assign(-4, nullptr, nullptr);
	Grid::GetGrid()[(int)np.y][(int)np.x].assign(-4, this, nullptr);
}

