#include "food.h"
#include "grid.h"

Food::Food(sf::Vector2f position) {
	setFillColor(sf::Color::Magenta);
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

	spawn();

	Grid::Assign((int)np.y, (int)np.x, { -3, nullptr, this, { m_smell_strength, 0.f } }, sf::Vector2i(np.y, np.x));
}

void Food::spawn() {
	for (int i = 0; i < m_radius; i++) {
		sf::Vector2i p = sf::Vector2i(getPosition());
		sf::Vector2i limit = sf::Vector2i(Grid::getWidth(), Grid::getHeight());

		if (p.x - i <= i)
			p.x = i;
		if (p.x + i >= limit.x)
			p.x = limit.x - 1 - i;
		if (p.y - i <= i)
			p.y = i;
		if (p.y + i >= limit.y)
			p.y = limit.y - 1 - i;

		float smell = m_smell_strength * m_decay / i;

		for (int j = p.x - i; j <= p.x + i; j++) {
			for (int k = p.y - i; k <= p.y + i; k++) {
				Grid::Assign(k, j, { -2, nullptr, nullptr, { smell, 0.f } });
			}

			Grid::Assign(p.y, j, { -2, nullptr, nullptr, { smell, 0.f } });
		}

		for (int k = p.y - i; k <= p.y + i; k++) {
			for (int j = p.x - i; j <= p.x + i; j++) {
				Grid::Assign(k, j, { -2, nullptr, nullptr, { smell, 0.f } });
			}
			Grid::Assign(k, p.x, { -2, nullptr, nullptr, { smell, 0.f } });
		}
	}

	Grid::UpdateSmellRadius();
}

int Food::getRadius() { return m_radius; }

void Food::despawn() {
	sf::Vector2f np = getPosition();
	
	
	auto c = Grid::GetPointer((int)np.y, (int)np.x);

	auto f = Grid::Food;
	for (int i = 0; i < Grid::Food.size(); i++) {
		if (c == Grid::Food.at(i).first) {
			Grid::Food.erase(Grid::Food.begin() + i);
			Grid::UpdateSmellRadius();
			break;
		}
	}

	/*auto it = f.begin();
	while (it != f.end()) {
		if (c == it->first) {
			it = Grid::Food.erase(it);
			Grid::UpdateSmellRadius();
			break;
		}
		else {
			++it;
		}
	}*/

	Grid::Assign((int)np.y, (int)np.x, { -5 });

	for (int i = 0; i < m_radius; i++) {
		sf::Vector2i p = sf::Vector2i(getPosition());
		sf::Vector2i limit = sf::Vector2i(Grid::getWidth(), Grid::getHeight());

		if (p.x - i <= i)
			p.x = i;
		if (p.x + i >= limit.x)
			p.x = limit.x - 1 - i;
		if (p.y - i <= i)
			p.y = i;
		if (p.y + i >= limit.y)
			p.y = limit.y - 1 - i;

		float smell = m_smell_strength * m_decay / i;

		for (int j = p.x - i; j <= p.x + i; j++) {
			for (int k = p.y - i; k <= p.y + i; k++) {
				Grid::Assign(k, j, { -5 });
			}

			Grid::Assign(p.y, j, { -5 });
		}

		for (int k = p.y - i; k <= p.y + i; k++) {
			for (int j = p.x - i; j <= p.x + i; j++) {
				Grid::Assign(k, j, { -5 });
			}
			Grid::Assign(k, p.x, { -5 });
		}
	}
}
