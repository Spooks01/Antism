#pragma once

class Pheromone
{
public:
	Pheromone() {

	}
	
	void update() {
		m_strength -= m_decay;
	}

private:
	float m_strength = 100;
	float m_decay = 1.0f;
};

