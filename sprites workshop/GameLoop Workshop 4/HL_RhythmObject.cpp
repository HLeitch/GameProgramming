#include "HL_RhythmObject.h"

HL_RhythmObject::HL_RhythmObject():HL_GameObject()
{
	active = false;


}

void HL_RhythmObject::Render(SDL_Renderer* renderer)
{
	if (active)
	{
		if(pressed){ SDL_SetRenderDrawColor(renderer, R, 255, B, 255); }
		else { SDL_SetRenderDrawColor(renderer, R, G, 255, 255); }

	myRect->x = x;
	myRect->y = y;
	myRect->w = width;
	myRect->h = height;

	SDL_RenderFillRect(renderer, myRect);
	}
}




