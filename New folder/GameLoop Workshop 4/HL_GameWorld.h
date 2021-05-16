#pragma once
#include <SDL.h>
#include <vector>
#include "HL_GameObject.h"
#include "HL_GameObjectContainer.h"
#include "HL_RhythmObjectContainer.h"
#include "HL_Rectangle.h"
#include "HL_Timer.h"
#include "GameWindow.h"
#include "HL_Square.h"
#include "HL_Vector2D.h"
#include "HL_FileLogger.h"
#include "HL_SimpleSprite.h"
#include "TextureManager.h"
#include "HL_Wall.h"
#include "HL_Enemy.h"

#include "HL_Player.h"
#include "HL_Bullet.h"
#include "HL_BulletContainer.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#define MAX_KEYS (528)


#define PLAYER  1
#define ENEMY  2
#define BULLET  3
#define WALL  4

enum PickupType
{
	NO_PICKUP = 0,
	HEALTH_PICKUP = 1,
	SPEED_PICKUP = 2,
	ROTATION_PICKUP = 3
};

enum HL_Event
{
	OTHER_EVENT,
	PLAYER_DAMAGED_EVENT,
	ITEM_USE_EVENT,
	ENEMY_DIED_EVENT,
	TIMER_EVENT,
	BULLET_IMPACT_EVENT
	
};

class HL_GameWorld
{
private:
	//Timer things

	HL_Timer* timer = &gTimer;

	//Time between updates. Will change framerate if modified
	const int delta_Time = 15;
	int lastDeltaTime;

	// If true, disables game loop.
	bool done = false;

public:
	//HL_GameWorld();
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event _event;
	TextureManager* theTextureManager = TextureManager::GetInstance();

	HL_GameWorld();

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
	
	SimpleSprite testSprite = SimpleSprite( 0,0,17,18);

	HL_Player* player = nullptr;
	HL_Bullet* _testBullet = nullptr;

	/// <summary>
	/// Add gameObjects which are subject to the typical game loop here!
	/// </summary>
	HL_GameObjectContainer _GameEventsObjectContainer;
	HL_GameObjectContainer _ColliderObjects;

	HL_BulletContainer* _playersBulletContainer;

	int Sprite_Height = 18;
	int Sprite_Width = 17;
	int Sprite_Frame = 0;
	int sprite_NumFrames = 4;
	int spritePlaybackRate = 75;
	/////////////////////////
};

