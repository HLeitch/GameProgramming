#pragma once
#include "HL_GameObject.h"
#include <vector>
#include <iostream>
#include "SDL.h"
class HL_GameObjectContainer
{
public:
	HL_GameObjectContainer();
	~HL_GameObjectContainer();

	void Init(int eY, int eX, float eDirX, float eDirY, int eNum);
	void Add(int X, int Y);


	virtual void Render(SDL_Renderer* aRenderer);
	virtual void Update();
	virtual void Input(SDL_Event* _event);

	void ChangeColour(int r, int g, int b);

	std::vector<HL_GameObject*> aListofGameObjects;
	int X, Y, Num;
	float dirX, dirY;

};

