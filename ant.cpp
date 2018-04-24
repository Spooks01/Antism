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
	sf::Vector2f pos = getPosition();
	sf::Vector2i limit = Grid::GetSize();
	float x = pos.x;
	float y = pos.y;
	float dx = 0;
	float dy = 0;
	float scan[3][3];

	// Path Selection Formula
	for (int a = 0; a < sizeof(*scan) / sizeof(**scan); a++) {
		for (int b = 0; b < sizeof(scan) / sizeof(*scan); b++) {
			if (!(a == 1 && b == 1)) {
				if (!((x + (a - 1)) < 0 || (x + (a - 1)) >= limit.x || (y + (b - 1)) < 0 || (y + (b - 1)) >= limit.y)) {
					pstr = Grid::GetGrid()[(int)(y + (b - 1))][(int)(x + (a - 1))].attributes.second;
					sstr = Grid::GetGrid()[(int)(y + (b - 1))][(int)(x + (a - 1))].attributes.first;

					if ((pow(pstr, alpha) * pow(sstr, beta)) != 0) { // If there is adjacent pheromone AND adjacent smell
						scan[a][b] = (pow(pstr, alpha) * pow(sstr, beta)) / (pow(pstr, alpha) + pow(sstr, beta));
					}
					else if ((pow(pstr, alpha) + pow(sstr, beta) == 0)) { // If there is no adjacent pheromone or smell
						scan[a][b] = 2;
					}
					else {
						scan[a][b] = (pow(pstr, alpha) + pow(sstr, beta)); // If there is only adjacent pheromone OR adjacent smell
					}
				}
				else {
					scan[a][b] = -1;
				}
			}
			else {
				scan[a][b] = -1;
			}
		}
	}

	// Directional test (north-east)
	// scan[2][0] = 5;

	// Calculate sum of scan[][] 
	float sum = 0;
	for (int a = 0; a < sizeof(*scan) / sizeof(**scan); a++) {
		for (int b = 0; b < sizeof(scan) / sizeof(*scan); b++) {
			if (scan[a][b] != -1) {
				sum += scan[a][b];
			}
		}
	}


	// std::cout << "SUM: " << sum << std::endl;

	// Normalisation of scan[][] to range 0...1
	for (int a = 0; a < sizeof(*scan) / sizeof(**scan); a++) {
		for (int b = 0; b < sizeof(scan) / sizeof(*scan); b++) {
			if (scan[a][b] != -1) {
				scan[a][b] /= (sum * pow(100, -1));
				// std::cout << scan[a][b] << std::endl;
			}
		}
	}

	// Fitness Proportionate Selection (roulette wheel selection)
	float random = ((rand() % 100 + 1));
	// std::cout << "random: " << random << std::endl;
	float lower = 0;
	float upper = 0;
	for (int a = 0; a < sizeof(*scan) / sizeof(**scan); a++) {
		for (int b = 0; b < sizeof(scan) / sizeof(*scan); b++) {
			if (scan[a][b] != -1) {
				upper = lower + scan[a][b];
				// std::cout << "lower: " << lower << std::endl;
				// std::cout << "upper: " << upper << std::endl;
				if (lower < random && random <= upper) {
					dx = (int)(a - 1);
					dy = (int)(b - 1);
				}
				lower += scan[a][b];
			}
		}
	}

	move(sf::Vector2f((float)dx, (float)dy));
	//m_health--;

	int count = 5;

	auto qq = m_trail.begin();
	//std::cout << " --------------- SET ----------------- " << std::endl;
	while (qq != m_trail.end() && count > 0) {
		auto v = *qq;

		//std::cout << "Size: " << m_trail.size() << "; Count: " << count << " " << (*qq).y << " " << (*qq).x << " + " << Grid::Get((*qq).y, (*qq).x).attributes.second << std::endl;

/*
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
			*/
		count--;		
	}


	//std::cout << m_trail.size() << std::endl;
	

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
