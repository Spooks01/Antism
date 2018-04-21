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

void Ant::update(int frame) {
	float x = (float)(rand() % 1 + 1);
	float y = (float)(rand() % 1 + 1);

	int dx = rand() % 2 + 1;
	int dy = rand() % 2 + 1;

	if (dx == 2)
		x = -x;
	if (dy == 2)
		y = -y;

	move(sf::Vector2f((float)x, (float)y));
	
	//m_health--;

	if (m_identifier < 0) {
		sf::Vector2i pos = (*m_trail.begin());
		Grid::Assign(pos.x, pos.y, { -2 });

		m_trail.erase(m_trail.begin());
	}

	if (frame % 60 == 0) {
		auto v = m_trail.front();
		if (Grid::Get(v.y, v.x).attributes.second <= m_pheromone) {
			Grid::Assign(v.y, v.x, { -2 });
			m_trail.pop_front();
			
			m_pvertices.pop_back();
			m_pvertices.pop_back();
			m_pvertices.pop_back();
			m_pvertices.pop_back();
		}
		else
			Grid::Assign(v.y, v.x, { -2, nullptr, nullptr, { 0, -m_pheromone } });
	}
		
}

float Ant::getHealth() {
	return m_health;
}

std::deque<sf::Vector2i> Ant::getTrail()
{
	return m_trail;
}

void Ant::move(sf::Vector2f offset) {
	sf::Vector2f cp = getPosition();
	sf::Vector2f np = cp + offset;

	sf::Vector2i limit = Grid::GetSize();
	if (np.x < 0)
		np.x = cp.x + 1;
	else if (np.x >= limit.x)
		np.x = cp.x - 1;

	if (np.y < 0)
		np.y = cp.y + 1;
	else if (np.y >= limit.y)
		np.y = cp.y - 1;

	m_trail.push_back(sf::Vector2i(cp));
	setPosition(np);
	
	Grid::Assign((int)cp.y, (int)cp.x, { -2, nullptr, nullptr, { 0.f, m_pheromone } }, sf::Vector2i((int)cp.x, (int)cp.y));
	Grid::Assign((int)cp.y, (int)cp.x, { -4, nullptr, nullptr });
	Grid::Assign((int)np.y, (int)np.x, { -4, this, nullptr });

	m_trail.push_back(sf::Vector2i(cp));

	sf::Vertex vertices[4];

	vertices[0] = { sf::Vector2f(cp.x, cp.y) + sf::Vector2f(0, 0), sf::Color::Cyan };
	vertices[1] = { sf::Vector2f(cp.x, cp.y) + sf::Vector2f(1, 0), sf::Color::Cyan };
	vertices[2] = { sf::Vector2f(cp.x, cp.y) + sf::Vector2f(1, 1), sf::Color::Cyan };
	vertices[3] = { sf::Vector2f(cp.x, cp.y) + sf::Vector2f(0, 1), sf::Color::Cyan };

	m_pvertices.insert(m_pvertices.begin(), vertices[0]);
	m_pvertices.insert(m_pvertices.begin(), vertices[1]);
	m_pvertices.insert(m_pvertices.begin(), vertices[2]);
	m_pvertices.insert(m_pvertices.begin(), vertices[3]);

	//m_pvertices.push_back(vertices[0]);
	//m_pvertices.push_back(vertices[1]);
	//m_pvertices.push_back(vertices[2]);
	//m_pvertices.push_back(vertices[3]);
}