#pragma once
#include <SDL.h>
#include <vector>
#include "HL_GameContainerSquare.h"
#include "HL_GameObject.h"
#include "HL_Rectangle.h"
#include "HL_Timer.h"
#include "GameWindow.h"
#include "HL_Square.h"
#include "HL_Vector2D.h"

#define MAX_KEYS (256)
#define gWorldSize (300)


class HL_GameWorld
{
private:
	//Timer things

	HL_Timer* timer;

	//Time between updates. Will change framerate if modified
	const int delta_Time = 3;
	
	// If true, disables game loop.
	bool done = false;

public:
	//HL_GameWorld();
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event _event;


	void Init();

	void ChangeState();

	void Input();
	int randColorElement();
	void Update();
	void WorldRendering();
	void RenderPoint(int i, int j);
	void Render();
	
	//Creates game loop
	void Run();
	

	void Quit();

	int countNeighbour(int cellx, int celly);
	bool paused = false;
	
	int cellEdgeLength = 4;

	int mouseX = 0;
	int mouseY = 0;
	

	//keyboard Handler
    bool gKeys[MAX_KEYS];

	bool gWorld[gWorldSize][gWorldSize];
	bool gNewWorld[gWorldSize][gWorldSize];

	int chanceOfAliveAtStart = 50;

	SDL_Rect renderingRectangle;

	/////////////////////////
	//GAMEOBJECTS 

	HL_GameContainerSquare aGameContainerSquare;

	
	/////////////////////////
};

