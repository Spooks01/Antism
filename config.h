#pragma once
#include <fstream>
class Config
{
public:
	Config();
	~Config();
	static void loadConfig(std::fstream *f);
	static int applicationWidth;
	static int applicationHeight;
	static bool vsync;
	static float pheremoneDecay;
	static float smellStrength;
	static float smellRadius;
};

