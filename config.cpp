#include "config.h"

int Config::applicationWidth = 0;
int Config::applicationHeight = 0;
bool Config::vsync = true;


Config::Config()
{
}


Config::~Config()
{
}

void Config::genDefaults() {
	Config::applicationWidth = 1280;
	Config::applicationHeight = 720;
	Config::vsync = true;
}
