#pragma once
#include <SDL.h>
#include "HL_GameObject.h"
#include "HL_Rectangle.h"
#include "HL_Timer.h"
#include "GameWindow.h"

#define MAX_KEYS (256)
#define MOVE_LEFT 'w'

class HL_GameWorld
{
private:
	//Timer things

	HL_Timer* timer;

	//Time between updates. Will change framerate if modified
	const int delta_Time = 6;

	// If true, disables game loop.
	bool done = false;

public:
	//HL_GameWorld();
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event _event;


	void Init();

	void Input();
	void Update();
	void Render();
	
	//Creates game loop
	void Run();
	

	void Quit();
	
	

	//keyboard Handler
    bool gKeys[MAX_KEYS];

	/////////////////////////
	//GAMEOBJECTS 



	HL_Rectangle* aRectangle;
	/////////////////////////
};

