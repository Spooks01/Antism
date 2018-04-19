#include "config.h"
#include <fstream>
#include <string>
int Config::applicationWidth = 1280;
int Config::applicationHeight = 720;
bool Config::vsync = true;

float Config::pheremoneDecay = 0.0f;
float Config::smellStrength = 0.0f;
float Config::smellRadius = 0.0f;


Config::Config()
{
}


Config::~Config()
{
}
std::string temp;
std::string::size_type sz;
void Config::loadConfig(std::fstream *f) {
	std::getline(*f, temp);
	pheremoneDecay = std::stof(temp, &sz);
	std::getline(*f, temp);
	smellStrength = std::stof(temp, &sz);
	std::getline(*f, temp);
	smellRadius = std::stof(temp, &sz);
}
