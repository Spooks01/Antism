#include "config.h"
#include <fstream>
#include <string>
int Config::applicationWidth = 1280;
int Config::applicationHeight = 720;
bool Config::vsync = true;

float Config::PheremoneDecay = 0.0f;
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
std::fstream *file;
void Config::loadConfig(std::fstream *f) {
	std::getline(*f, temp);
	PheremoneDecay = std::stof(temp, &sz);
	std::getline(*f, temp);
	smellStrength = std::stof(temp, &sz);
	std::getline(*f, temp);
	smellRadius = std::stof(temp, &sz);
	file = f;
}


void Config::writeDecay(float stat){
	//make this write the float to the first line of cfg

}
