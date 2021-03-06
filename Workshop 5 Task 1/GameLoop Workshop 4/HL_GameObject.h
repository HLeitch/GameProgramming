#pragma once
#include "SDL.h"

#include <iostream>
#include "HL_Vector2D.h"
class HL_GameWorld;

class HL_GameObject
{
public:

	virtual void Init();
	virtual void Input(SDL_Event);
	virtual void Update();
	virtual void Render(SDL_Renderer* theRenderer);

	HL_GameObject();
	virtual ~HL_GameObject();

	static int SquareCounterTotal;
	int SquareCounter;

	HL_GameWorld* parent;

private:
	SDL_Rect rect;
	HL_Vector2D velocity;

};

