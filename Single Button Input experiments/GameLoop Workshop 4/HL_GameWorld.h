#pragma once
#include <SDL.h>
#include <vector>
#include "HL_GameObjectContainer.h"
#include "HL_RhythmObjectContainer.h"
#include "HL_GameObject.h"
#include "HL_Rectangle.h"
#include "HL_Timer.h"
#include "GameWindow.h"
#include "HL_Square.h"
#include "HL_Vector2D.h"
#include "HL_FileLogger.h"

#define MAX_KEYS (256)


class HL_GameWorld
{
private:
	//Timer things

	HL_Timer* timer;

	//Time between updates. Will change framerate if modified
	const int delta_Time = 33;
	int lastDeltaTime;

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
	void RhythmReset();
	void Render();

	//Creates game loop
	void Run();


	void Quit();

	int randColorElement();

	//keyboard Handler
	bool gKeys[MAX_KEYS];

	/////////////////////////
	//GAMEOBJECTS 

	int gameTime = 30000;

	int timerWidth = 800;

	int gameRoundTimer = 0;

	int maxGameRoundTime = 3000;

	/// <summary>
	/// Time Since game start in ms
	/// </summary>
	int gameTimer = 0;

	HL_GameObject* timerBar;
	
	HL_GameObject* indicatorSquare;

	HL_GameObjectContainer aGameContainerSquare;
	HL_RhythmObjectContainer* rhythmObjects;


	/////////////////////////
};

