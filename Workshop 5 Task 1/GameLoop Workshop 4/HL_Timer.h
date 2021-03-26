#pragma once

#include <iostream>
#include <SDL.h>

class HL_Timer
{
private:
	/// <summary>
	/// SDL Time on start of timer
	/// </summary>
	int startTicks;

public:

	HL_Timer();

	void resetTicksTimer();
	int getTicks();

};

