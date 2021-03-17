#include "SinusoidalPoint.h"

SinusoidalPoint::SinusoidalPoint(int xval, int yval)
{

	myPoint = new SDL_Point();
	myPoint->x = xval;
	myPoint->y = yval;

}

void SinusoidalPoint::Render(SDL_Renderer* theRenderer)
{
	SDL_SetRenderDrawColor(theRenderer, 255, 255, 255, 255);
	SDL_RenderDrawPoint(theRenderer, myPoint->x, myPoint->y);
		
}