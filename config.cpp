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
	file->clear();
}

void Config::loadConfig() {
	file->seekg(0, file->beg);
	std::getline(*file, temp);
	PheremoneDecay = std::stof(temp, &sz);
	std::getline(*file, temp);
	smellStrength = std::stof(temp, &sz);
	std::getline(*file, temp);
	smellRadius = std::stof(temp, &sz);
	file->clear();
}


void Config::writeConfig(){
	//make this write the float to the first line of cfg

}
