#pragma once
#include <iostream>
#include "SDL.h"
#include <fstream>
#include <ctime>


class HL_FileLogger
{
public:
	HL_FileLogger(const std::string& logFilePath);
	~HL_FileLogger();

	void LoggingFunction(void* userdata, int category, SDL_LogPriority priority, const char* message);

	static void LogCB(void* userdata, int category, SDL_LogPriority priority, const char* message);

private:
	std::ofstream logFile;
};

