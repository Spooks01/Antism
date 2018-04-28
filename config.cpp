#include "config.h"
#include <fstream>
#include <string>
int Config::applicationWidth;
int Config::applicationHeight;
bool Config::vsync = true;

float Config::PheremoneDecay = 0.25f;
float Config::smellStrength = 0.0f;
float Config::FoodSmellRadius = 0.0f;
int Config::MaxFrames = 10;
float Config::AlphaParam = 1;
float Config::BetaParam = 8;
int Config::ColonySize = 100;
float Config::MaxSmell = 100;
float Config::MaxPheromone = 100;
int Config::FoodCapacity = 10;
int Config::QueenCapacity = 1;

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
	file = f;
	std::getline(*file, temp);
	std::getline(*file, temp);
	PheremoneDecay = std::stof(temp, &sz);
	std::getline(*file, temp);
	std::getline(*file, temp);
	smellStrength = std::stof(temp, &sz);
	std::getline(*file, temp);
	std::getline(*file, temp);
	FoodSmellRadius = std::stof(temp, &sz);
	std::getline(*file, temp);
	std::getline(*file, temp);
	applicationWidth = std::stof(temp, &sz);
	std::getline(*file, temp);
	std::getline(*file, temp);
	applicationHeight = std::stof(temp, &sz);
	file->clear();
	file->close();
}

void Config::loadConfig() {
	file->open("config.cfg");
	file->seekg(0, file->beg);
	std::getline(*file, temp);
	std::getline(*file, temp);
	PheremoneDecay = std::stof(temp, &sz);
	std::getline(*file, temp);
	std::getline(*file, temp);
	smellStrength = std::stof(temp, &sz);
	std::getline(*file, temp);
	std::getline(*file, temp);
	FoodSmellRadius = std::stof(temp, &sz);
	std::getline(*file, temp);
	std::getline(*file, temp);
	applicationWidth = std::stof(temp, &sz);
	std::getline(*file, temp);
	std::getline(*file, temp);
	applicationHeight = std::stof(temp, &sz);
	file->clear();
	file->close();
}


void Config::writeConfig(){
	file->open("config.cfg", std::ios::out | std::ios::trunc);
	*file << "//pheremone decay rate" << std::endl
		<< PheremoneDecay << std::endl
		<< "//strength of food smell. Is this even being used?" << std::endl
		<< smellStrength << std::endl
		<< "//Radius of new food placed" << std::endl
		<< FoodSmellRadius << std::endl
		<< "//screen resolution width" << std::endl
		<< applicationWidth << std::endl
		<< "//screen resolution height" << std::endl
		<< applicationHeight << std::endl;
	file->close();
}

void Config::loadDefaultValues() {
	Config::AlphaParam = 1;
	Config::BetaParam = 5;
	Config::PheremoneDecay = 0.01;
	Config::FoodSmellRadius = 25;
	Config::ColonySize = 100;
	Config::writeConfig();
}

void Config::loadDefaultColonySize() {
	Config::ColonySize = 100;
}
