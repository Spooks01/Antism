#include "colony.h"

#include <thread>

Colony::Colony(sf::Vector2f center) {
	m_center = center;

	m_iterator = m_ants.begin();
}

void Colony::addAnt(Ant* ant) {
	m_ants.push_back(ant);
}

void Colony::removeAnt(int index) {
	m_ants.erase(m_ants.begin() + index);
}

void Colony::spawnAnt(sf::Vector2f position) {
	m_ants.push_back(new Ant(position));
}

void Colony::spawnAnt() {
	m_ants.push_back(new Ant());
}

void Colony::update(int frame) {

	int stage = m_ants.size() / Config::MaxFrames + 1;

	std::vector<sf::Vector2i> pha;
	//sf::Vector2i* pha = new sf::Vector2i[4 * m_ants.size()];
	int k = 0;
	m_numFrames = frame;

	for (int i = 0; i < stage; i++) {
		if (frame * stage + i < m_ants.size()) {
			m_ants.at(frame * stage + i)->update();

			int count = 1 / Config::PheremoneDecay + 1;
			//int count = 5;
			//std::cout << " --------------- SET ----------------- " << std::endl;

			auto p = m_ants.at(frame * stage + i)->getPosition();
			auto v = m_ants.at(frame * stage + i)->getTTrail();
			auto t = m_ants.at(frame * stage + i)->getTrail();
			auto b = v->begin();
			int ite = 4;
			while (b != v->end() && count > 0) {
				auto p = *b;
				//std::cout << "Size: " << v->size() << "; Count: " << count << " " << p.y << " " << p.x << " + " << Grid::Get(p.y, p.x).attributes.second << std::endl;

				if ((Grid::Get(p.y, p.x).attributes.second < Config::PheremoneDecay || Grid::Get(p.y, p.x).attributes.second == 0)) {
					Grid::Assign(p.y, p.x, { -5 });

					b = v->erase(b);

					t->pop_back();
					t->pop_back();
					t->pop_back();
					t->pop_back();
				}
				else {
					if (std::find(pha.begin(), pha.end(), p) == pha.end()) {
						Grid::Assign(p.y, p.x, { -2, nullptr, nullptr,{ 0, -Config::PheremoneDecay } });
					} else
						pha.push_back(p);
					/*
					if ((t->end() - 1)->color.a > 0) {

						(t->end() - 1)->color.a -= 50;
						(t->end() - 2)->color.a -= 50;
						(t->end() - 3)->color.a -= 50;
						(t->end() - 4)->color.a -= 50;
					}
					*/
					
					if (t->at(ite - 1).color.a > 0) {
						t->at(ite - 1).color.a = -25;
						t->at(ite - 2).color.a = -25;
						t->at(ite - 3).color.a = -25;
						t->at(ite - 4).color.a = -25;
						
					}
					
					++b;
					ite += 4;
				}
				
				count--;
			}

			if (m_ants.at(frame * stage + i)->getHealth() <= 0) {
				m_ants.erase(m_iterator + frame * stage + i);
			}
		}
	}

	
	
	m_queen->update();
	if (m_queen->getStatus()) {
		sf::Vector2f pos = sf::Vector2f(m_center.x, m_center.y + 3);
		//Grid::GetGrid()[(int)pos.y][(int)pos.x] = { 1, nullptr };

		//m_ants.push_back(new Ant(pos));

		m_queen->setStatus(false);
	}

	pha.clear();
}

void Colony::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	int stage = (m_ants.size() / Config::MaxFrames + 1);
	int k = 0;
	sf::Vertex* vertices = new sf::Vertex[m_ants.size() * 4];

	for (int i = 0; i < m_ants.size(); i++) {
	//	if (m_numFrames * stage + i < m_ants.size()) {
			auto v = m_ants.at(i)->getTrail();
			auto w = m_ants.at(i)->getVertices();

			if (v->size()) {
				target.draw(&(*v)[0], v->size(), sf::Quads);
			}

			vertices[k + 0] = w[0];
			vertices[k + 1] = w[1];
			vertices[k + 2] = w[2];
			vertices[k + 3] = w[3];

			k += 4;
		//}
	}

	target.draw(vertices, m_ants.size() * 4, sf::Quads);
	target.draw(*m_queen, states);
	/*
	auto i = m_ants.begin();
	auto k = 0;

	sf::Vertex* vertices = new sf::Vertex[m_ants.size() * 4];

	i = m_ants.begin();
	while (i != m_ants.end()) {
		auto v = (*i)->getTrail();
		auto w = (*i)->getVertices();

		if (v.size()) {
			target.draw(&v[0], v.size(), sf::Quads);
		}
			
		vertices[k + 0] = w[0];
		vertices[k + 1] = w[1];
		vertices[k + 2] = w[2];
		vertices[k + 3] = w[3];

		k += 4;
		
		++i;
	}

	target.draw(vertices, m_ants.size() * 4, sf::Quads);
	target.draw(*m_queen, states);
	*/
	delete[] vertices;
}

void Colony::generate(int size) {
	clean();

	m_generation = 1;

	m_queen = new Queen(m_center);
	Grid::Assign((int)m_center.y, (int)m_center.x, { -4, m_queen, nullptr });

	for (int i = 0; i < size; ++i) {
		int x = rand() % 100 + 1;
		int y = rand() % 100 + 1;

		int dx = rand() % 2 + 1;
		int dy = rand() % 2 + 1;

		if (dx == 2)
			x = -x;
		if (dy == 2)
			y = -y;

		sf::Vector2f pos = sf::Vector2f(m_center.x + x, m_center.y + y);
		Grid::Assign((int)pos.y, (int)pos.x, { 1, nullptr });

		m_ants.push_back(new Ant(pos));
	}

}

void Colony::clean() {
	index = 0;

	for (size_t i = 0; i < m_ants.size(); i++) {
		delete m_ants[i];
	}
	m_ants.clear();
}

void Colony::passFrames(int f) {
	m_numFrames = f;
}