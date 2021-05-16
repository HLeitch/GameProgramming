#pragma once
#include <iostream>
#include "SDL.h"
#include <fstream>
#include <ctime>
#include <map>


class HL_FileLogger
{
public:
	HL_FileLogger(const std::string& logFilePath);
	~HL_FileLogger();

	void LoggingFunction(void* userdata, int category, SDL_LogPriority priority, const char* message);

	void ErrorLoggingFunction(void* userdata, int category, SDL_LogPriority priority, const char* message);

	static void LogCB(void* userdata, int category, SDL_LogPriority priority, const char* message);

	bool getTime(char* buffer, int buffersize);

	bool isCurrentlyLogging;

	void SetLogging(bool log);

private:
	std::map<int, std::ofstream*> logFileMap;
	std::map<int, std::string> logStringMap;

	/// <summary>
	/// File currently outputting
	/// </summary>
	std::ofstream* destinationFile;

	std::ofstream* logFile;
	std::ofstream* applicationlogFile;
	std::ofstream* errorlogFile;
	std::ofstream* assertlogFile;
	std::ofstream* systemlogFile;
	std::ofstream* audiologFile;
	std::ofstream* videologFile;
	std::ofstream* renderlogFile;
	std::ofstream* inputlogFile;
	std::ofstream* testlogFile;

	bool isLogging;
};

