#pragma once
#include <fstream>
class Config
{
public:
	Config();
	~Config();
	static void loadConfig(std::fstream *f);
	static void writeDecay(float stat);
	static int applicationWidth;
	static int applicationHeight;
	static bool vsync;
	static float PheremoneDecay;
	static float smellStrength;
	static float smellRadius;
};

