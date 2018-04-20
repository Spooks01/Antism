#pragma once
#include <string>
#include "Config.h"
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
	float m_decay = Config::PheremoneDecay;
};

