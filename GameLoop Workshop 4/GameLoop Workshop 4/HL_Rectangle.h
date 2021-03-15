#pragma once
#include <iostream>
#include "SDL.h"
#include "HL_GameObject.h"

class HL_Rectangle: HL_GameObject
{
private:
	

	
	int width;
	int height;
	std::string myName = "Default rectangle";
	
	bool moving = true;
	

public:

	void Init();
	void Input(int whichKey);
	void Update();
	void Render(SDL_Renderer* theRenderer);
	
	SDL_Rect* myRect;
	int xPos;
	int yPos;

	HL_Rectangle(int xPos, int yPos, int width, int height);
	~HL_Rectangle();

	SDL_Color* myColour = new SDL_Color();
	int speed = 8;

};

