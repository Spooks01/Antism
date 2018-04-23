#include "ant.h"

Ant::Ant()
{
	m_vertices[0].color = sf::Color::Green;
	m_vertices[1].color = sf::Color::Green;
	m_vertices[2].color = sf::Color::Green;
	m_vertices[3].color = sf::Color::Green;

	m_health = float(rand() % 1500 + 1000);
}

Ant::Ant(sf::Vector2f position)
{
	setPosition(position);

	m_vertices[0].color = sf::Color::Green;
	m_vertices[1].color = sf::Color::Green;
	m_vertices[2].color = sf::Color::Green;
	m_vertices[3].color = sf::Color::Green;

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
	
	//m_health--;

	int count = 5;

	auto qq = m_trail.begin();
	//std::cout << " --------------- SET ----------------- " << std::endl;
	while (qq != m_trail.end() && count > 0) {
		auto v = *qq;

		//std::cout << "Size: " << m_trail.size() << "; Count: " << count << " " << (*qq).y << " " << (*qq).x << " + " << Grid::Get((*qq).y, (*qq).x).attributes.second << std::endl;


		if (Grid::Get(v.y, v.x).attributes.second < m_decay || Grid::Get(v.y, v.x).attributes.second == 0) {
			Grid::Assign(v.y, v.x, { -5 });

			qq = m_trail.erase(qq);

			m_pvertices.pop_back();
			m_pvertices.pop_back();
			m_pvertices.pop_back();
			m_pvertices.pop_back();
		}
		else {
			Grid::Assign(v.y, v.x, { -2, nullptr, nullptr,{ 0, -m_decay } });

			++qq;
		}
			
		count--;		
	}
}

float Ant::getHealth() {
	return m_health;
}

void Ant::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_vertices, 4, sf::Quads);
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

	setPosition(np);
	
	Grid::Assign((int)cp.y, (int)cp.x, { -4, nullptr, nullptr, { 0.f, m_pheromone } });
	Grid::Assign((int)np.y, (int)np.x, { -4, this, nullptr });

	m_trail.push_back(sf::Vector2i(cp));

	m_pvertices.insert(m_pvertices.begin(), { sf::Vector2f(cp.x, cp.y) + sf::Vector2f(0, 0), sf::Color::Cyan });
	m_pvertices.insert(m_pvertices.begin(), { sf::Vector2f(cp.x, cp.y) + sf::Vector2f(1, 0), sf::Color::Cyan });
	m_pvertices.insert(m_pvertices.begin(), { sf::Vector2f(cp.x, cp.y) + sf::Vector2f(1, 1), sf::Color::Cyan });
	m_pvertices.insert(m_pvertices.begin(), { sf::Vector2f(cp.x, cp.y) + sf::Vector2f(0, 1), sf::Color::Cyan });
}

void Ant::setPosition(sf::Vector2f position)
{
	m_vertices[0].position = position + sf::Vector2f(0, 0);
	m_vertices[1].position = position + sf::Vector2f(m_size, 0);
	m_vertices[2].position = position + sf::Vector2f(m_size, m_size);
	m_vertices[3].position = position + sf::Vector2f(0, m_size);
}
