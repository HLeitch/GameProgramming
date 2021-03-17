#pragma once
#include "HL_GameObject.h"
class SinusoidalPoint : public HL_GameObject
{

public:
	SinusoidalPoint(int xval,int yval);

	void Render(SDL_Renderer* myRenderer);
	SDL_Point* myPoint;

};

