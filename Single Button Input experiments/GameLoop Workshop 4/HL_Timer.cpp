#include "HL_Timer.h"

HL_Timer::HL_Timer()
{

	startTicks = 0;

};

/// <summary>
/// Resets the timer starting from the calling of this funcition
/// </summary>
void HL_Timer::resetTicksTimer()
{
	totalTicksSinceStart += getTicks();

	startTicks = SDL_GetTicks();

};

/// <summary>
/// Return time since start
/// </summary>
/// <returns></returns>
int HL_Timer::getTicks()
{
	return (SDL_GetTicks() - startTicks);

}
