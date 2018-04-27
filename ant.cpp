#include "ant.h"
#include "food.h"

Ant::Ant()
{
	m_vertices[0].color = sf::Color::Green;
	m_vertices[1].color = sf::Color::Green;
	m_vertices[2].color = sf::Color::Green;
	m_vertices[3].color = sf::Color::Green;

	m_health = float(rand() % 5000 + 2500);
}

Ant::Ant(sf::Vector2f position)
{
	setPosition(position);

	m_vertices[0].color = sf::Color::Green;
	m_vertices[1].color = sf::Color::Green;
	m_vertices[2].color = sf::Color::Green;
	m_vertices[3].color = sf::Color::Green;

	m_health = float(rand() % 5000 + 2500);
}

Ant::~Ant()
{
}

void Ant::setBlanc() {
	Grid::Assign((int)m_vertices[0].position.y, (int)m_vertices[0].position.x, { -4, nullptr, nullptr });

	m_vertices[0] = { sf::Vector2f(0, 0), sf::Color(0, 0, 0, 0)};
	m_vertices[1] = { sf::Vector2f(0, 0), sf::Color(0, 0, 0, 0)};
	m_vertices[2] = { sf::Vector2f(0, 0), sf::Color(0, 0, 0, 0)};
	m_vertices[3] = { sf::Vector2f(0, 0), sf::Color(0, 0, 0, 0)};
}

void Ant::update() {
	// std::cout << m_health << std::endl;

	if (alive) {
		if (m_health <= 0) {
			alive = false;
			setBlanc();

		}

		if (!hasFood) {
			getFood();
		}
		else {
			goHome();
		}

		m_health--;
	}
}

void Ant::getFood() {
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
					float pstr = Grid::GetGrid()[(int)(y + (b - 1))][(int)(x + (a - 1))].attributes.second;
					float sstr = Grid::GetGrid()[(int)(y + (b - 1))][(int)(x + (a - 1))].attributes.first;
					if (((Food*)Grid::Get((int)(y + (b - 1)), (int)(x + (a - 1))).food)) {
						hasFood = true;
						auto f = ((Food*)Grid::Get((int)(y + (b - 1)), (int)(x + (a - 1))).food);
						std::cout << f->getCapacity() << std::endl;
						if (f->getCapacity() > 1) {
							f->lowerCapacity();
						}
						else
							f->despawn(); 
						std::cout << " food found" << std::endl;
					}

					if ((pow(pstr, alpha) * pow(sstr, beta)) != 0) { // If there is adjacent pheromone AND adjacent smell
						scan[a][b] = (pow(pstr, alpha) * pow(sstr, beta)) / (pow(pstr, alpha) + pow(sstr, beta));
					}
					else if ((pow(pstr, alpha) + pow(sstr, beta) == 0)) { // If there is no adjacent pheromone or smell
						scan[a][b] = 1;
					}
					else {
						scan[a][b] = pow(pow(pstr, alpha) + pow(sstr, beta), 0.5); // If there is only adjacent pheromone OR adjacent smell
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
	// std::cout << "RANDOM: " << random << std::endl;
	float lower = 0;
	float upper = 0;
	for (int a = 0; a < sizeof(*scan) / sizeof(**scan); a++) {
		for (int b = 0; b < sizeof(scan) / sizeof(*scan); b++) {
			if (scan[a][b] != -1) {
				upper = lower + scan[a][b];
				// std::cout << "LOWER: " << lower << std::endl;
				// std::cout << "UPPER: " << upper << std::endl;
				if (lower < random && random <= upper) {
					dx = (int)(a - 1);
					dy = (int)(b - 1);
				}
				lower += scan[a][b];
			}
		}
	}

	move(sf::Vector2f((float)dx, (float)dy));
}

void Ant::goHome() {
	float dx = 0;
	float dy = 0;
	if (!m_trailoff.empty()) {
		sf::Vector2f pos = m_trailoff.back();
		m_trailoff.pop_back();
		dx = -pos.x;
		dy = -pos.y;

		move(sf::Vector2f((float)dx, (float)dy));
	}
	else {
		std::cout << "home now" << std::endl;
		hasFood = false;
		getFood();
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

	if (!hasFood) {
		m_trailoff.push_back(sf::Vector2f(offset));
	}

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
