#pragma once
#include "SDL.h"
#include <iostream>

class HL_GameObject
{
public:

	void Init();
	void Input(int whichKey);
	void Update();
	void Render(SDL_Renderer* theRenderer);


};

