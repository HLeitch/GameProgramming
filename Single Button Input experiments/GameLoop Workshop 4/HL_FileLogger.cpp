
#include "HL_FileLogger.h"


HL_FileLogger::HL_FileLogger(const std::string& logFilePath)
{
	//open log file
	logFile = std::ofstream(logFilePath.c_str());
	
	//Log through new function
	SDL_LogSetOutputFunction(&HL_FileLogger::LogCB,(void *)this);
}

HL_FileLogger::~HL_FileLogger()
{
	logFile.close();

}

void HL_FileLogger::LoggingFunction(void* userdata, int category, SDL_LogPriority priority, const char* message)
{
	printf("[%s]", std::time);
}

void HL_FileLogger::LogCB(void* userdata, int category, SDL_LogPriority priority, const char* message)
{
	HL_FileLogger* ptr = (HL_FileLogger*)userdata;
	if (ptr)
	{
		ptr->LoggingFunction(userdata, category, priority, message);
	}
}


