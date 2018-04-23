#include "config.h"
#include <fstream>
#include <string>
int Config::applicationWidth = 1280;
int Config::applicationHeight = 720;
bool Config::vsync = true;

float Config::PheremoneDecay = 0.0f;
float Config::smellStrength = 0.0f;
float Config::FoodSmellRadius = 0.0f;
int Config::MaxFrames = 10;


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
	FoodSmellRadius = std::stof(temp, &sz);
	file = f;
	file->clear();
	file->close();
}

void Config::loadConfig() {
	file->open("config.cfg");
	file->seekg(0, file->beg);
	std::getline(*file, temp);
	PheremoneDecay = std::stof(temp, &sz);
	std::getline(*file, temp);
	smellStrength = std::stof(temp, &sz);
	std::getline(*file, temp);
	FoodSmellRadius = std::stof(temp, &sz);
	file->clear();
	file->close();
}


void Config::writeConfig(){
	file->open("config.cfg", std::ios::out | std::ios::trunc);
	*file << PheremoneDecay << "\n" << smellStrength << "\n" << FoodSmellRadius;
	file->close();
}
