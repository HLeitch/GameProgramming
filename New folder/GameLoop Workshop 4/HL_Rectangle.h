#pragma once
#include <iostream>
#include "HL_GameObject.h"
#include "SDL.h"



class HL_Rectangle : public HL_GameObject
{
private:
	

	
	int width;
	int height;
	std::string myName = "Default rectangle";
	
	bool moving = true;
	

public:

	void Init(int xPos, int yPos, int width, int height);
	void Input(int whichKey);
	void Update();
	void Render(SDL_Renderer* theRenderer);
	
	SDL_Rect* myRect;
	int xPos;
	int yPos;

	HL_Rectangle();
	~HL_Rectangle();

	SDL_Color* myColour = new SDL_Color();
	int speed = 8;

};

