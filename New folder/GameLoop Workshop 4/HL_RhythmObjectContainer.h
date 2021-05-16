#pragma once
#include "HL_RhythmObject.h"
#include <vector>
#include <iostream>
#include "SDL.h"
class HL_RhythmObjectContainer
{

	
	public:
		HL_RhythmObjectContainer();
		~HL_RhythmObjectContainer();

		void Init(int eX, int eY, float eDirX, float eDirY, int eNum);
		void Add(int X, int Y);


		void Render(SDL_Renderer* aRenderer);
		void Update();
		void Input(SDL_Event* _event);

		void ChangeColour(int r, int g, int b);

		int PressedObjects();


		std::vector<HL_RhythmObject*> aListofRhythmObjects;
		int X, Y, Num;
		float dirX, dirY;

		int roundCounter = 0;
		int activeObjects =0;

	
};

