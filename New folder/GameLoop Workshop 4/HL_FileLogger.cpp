
#include "HL_FileLogger.h"



HL_FileLogger::HL_FileLogger(const std::string& logFilePath)
{
	//open log file
	logFile = new std::ofstream(logFilePath.c_str());

	
	std::string applicationFileLocation = "Log/application";
	applicationFileLocation += logFilePath.c_str();
	applicationlogFile = new std::ofstream(applicationFileLocation);
	logFileMap.emplace(SDL_LOG_CATEGORY_APPLICATION, applicationlogFile);
	logStringMap.emplace(SDL_LOG_CATEGORY_APPLICATION, "APPLICATION");

	//open error log File
	std::string errorFileLocation = "Log/error";
	errorFileLocation += logFilePath.c_str();
	errorlogFile = new std::ofstream(errorFileLocation);
	logFileMap.emplace(SDL_LOG_CATEGORY_ERROR, errorlogFile);
	logStringMap.emplace(SDL_LOG_CATEGORY_ERROR, "ERROR");

	std::string assertFileLocation = "Log/assert";
	assertFileLocation += logFilePath.c_str();
	assertlogFile = new std::ofstream(assertFileLocation);
	logFileMap.emplace(SDL_LOG_CATEGORY_ASSERT, assertlogFile);
	logStringMap.emplace(SDL_LOG_CATEGORY_ASSERT, "ASSERT");

	std::string systemFileLocation = "Log/system";
	systemFileLocation += logFilePath.c_str();
	systemlogFile = new std::ofstream(systemFileLocation);
	logFileMap.emplace(SDL_LOG_CATEGORY_SYSTEM, systemlogFile);
	logStringMap.emplace(SDL_LOG_CATEGORY_SYSTEM, "SYSTEM");

	std::string audioFileLocation = "Log/audio";
	audioFileLocation += logFilePath.c_str();
	audiologFile = new std::ofstream(audioFileLocation);
	logFileMap.emplace(SDL_LOG_CATEGORY_AUDIO, audiologFile);
	logStringMap.emplace(SDL_LOG_CATEGORY_AUDIO, "AUDIO");

	std::string videoFileLocation = "Log/video";
	videoFileLocation += logFilePath.c_str();
	videologFile = new std::ofstream(videoFileLocation);
	logFileMap.emplace(SDL_LOG_CATEGORY_VIDEO, videologFile);
	logStringMap.emplace(SDL_LOG_CATEGORY_VIDEO, "VIDEO");

	std::string renderFileLocation = "Log/render";
	renderFileLocation += logFilePath.c_str();
	renderlogFile = new std::ofstream(renderFileLocation);
	logFileMap.emplace(SDL_LOG_CATEGORY_RENDER, renderlogFile);
	logStringMap.emplace(SDL_LOG_CATEGORY_RENDER, "RENDER");

	std::string inputFileLocation = "Log/input";
	inputFileLocation += logFilePath.c_str();
	inputlogFile = new std::ofstream(inputFileLocation);
	logFileMap.emplace(SDL_LOG_CATEGORY_INPUT, inputlogFile);
	logStringMap.emplace(SDL_LOG_CATEGORY_INPUT, "INPUT");

	std::string testFileLocation = "Log/test";
	testFileLocation += logFilePath.c_str();
	testlogFile = new std::ofstream(testFileLocation);
	logFileMap.emplace(SDL_LOG_CATEGORY_TEST, testlogFile);
	logStringMap.emplace(SDL_LOG_CATEGORY_TEST, "TEST");



	//Log through new function
	SDL_LogSetOutputFunction(&HL_FileLogger::LogCB, (void*)this);
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_INFO);
	isLogging = true;

	SDL_Log("Log Files Created Successfully");
	SDL_LogError(SDL_LOG_CATEGORY_ERROR,"THIS IS A TEST ERROR. ALL IS GOOD DO NOT WORRY");
}

HL_FileLogger::~HL_FileLogger()
{
	logFile->close();
	errorlogFile->close();

}

void HL_FileLogger::LoggingFunction(void* userdata, int category, SDL_LogPriority priority, const char* message)
{
	if (isLogging)
	{
		char* timenow = new char[32];
		getTime(timenow, 32);

		std::cout << "[" << timenow << "] " << "[" << logStringMap.at(category) << "] " << message << std::endl;
		*logFile << "[" << timenow << "] " << "[" << logStringMap.at(category) << "] " << message << std::endl;

			*destinationFile << "[" << timenow << "] " << message << std::endl;
		
	}
}

//void HL_FileLogger::ErrorLoggingFunction(void* userdata, int category, SDL_LogPriority priority, const char* message)
//{
//	if (isLogging)
//	{
//		char* timenow = new char[32];
//		getTime(timenow, 32);
//
//		std::cout << "[" << timenow << "] " << "[" << "ERROR" << "] " << message << std::endl;
//		errorlogFile << "[" << timenow << "] " << message << std::endl;
//	}
//}

void HL_FileLogger::LogCB(void* userdata, int category, SDL_LogPriority priority, const char* message)
{
	HL_FileLogger* ptr = (HL_FileLogger*)userdata;
	if (ptr)
	{
		
		ptr->destinationFile = ptr->logFileMap.at(category);

		
			ptr->LoggingFunction(userdata, category, priority, message);
		
	}

}

bool HL_FileLogger::getTime(char* buffer, int buffersize)
{
	//Get the current time
	time_t currentTime = std::time(0);

	//Get time information from current time -- secs, mins, etc. and save into a struct
	struct tm* info = new tm();
	localtime_s(info, &currentTime);

	//Format the time to (day_num/month_num/year time)
	size_t written = strftime(buffer, buffersize, "%d/%m/%y %T", info);

	//And return if the string was written or not
	return written != 0;
}

void HL_FileLogger::SetLogging(bool log)
{

	this->isLogging = log;
}

