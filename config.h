#pragma once
class Config
{
public:
	Config();
	~Config();

	static void genDefaults();
	static int applicationWidth;
	static int applicationHeight;
	static bool vsync;
};

