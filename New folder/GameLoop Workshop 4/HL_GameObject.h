#pragma once
#include "SDL.h"
#include "HL_Vector2D.h"
#include "TextureManager.h"

#include "HL_Timer.h"
#include "HL_SimpleSprite.h"
#include "HL_GameObject.h"
#include "HL_Collider.h"
#include <iostream>
class HL_GameWorld;



/// <summary>
/// Class which can render a rect on the screen.
/// </summary>
class HL_GameObject
{
public:

	int x, y, height, width, R, G, B { 0 };
	double rotation = 0;

	HL_Vector2D realPosition = HL_Vector2D();

	virtual void Init(int xpos, int ypos, int w, int h);
	virtual void Input(SDL_Event* _event);

	virtual void Update();
	virtual void Render(SDL_Renderer* theRenderer);
	virtual void HasCollided(HL_Collider* otherCollider);

	HL_GameObject();
	virtual ~HL_GameObject();

	void SetColour(int newR, int newG, int newB);
	bool CopyColour(const HL_GameObject& otherGameObject);
	bool display = true;

	bool MOVE_LEFT = false;
	bool MOVE_RIGHT = false;
	bool MOVE_UP = false;
	bool MOVE_DOWN = false;

	HL_GameWorld* parent;
	
	bool Active = true;

	SDL_Rect* myRect;
	HL_Vector2D velocity;

	HL_Collider* myCollider = nullptr;

	std::string _objectName;
	int _objectType;
protected:

	//global texture manager
	TextureManager* theTextureManager;
	//current texture in gameobject
	SimpleSprite* sprite;
};

