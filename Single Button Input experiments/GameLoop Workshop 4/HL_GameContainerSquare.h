#pragma once
#include "HL_Square.h"
#include <vector>
#include <iostream>
#include "SDL.h"
class HL_GameContainerSquare
{
public:
	HL_GameContainerSquare();
	~HL_GameContainerSquare();

	void Init(int eY, int eX, float eDirX, float eDirY, int eNum);
	void Add(int X, int Y);


	void Render(SDL_Renderer* aRenderer);
	void Update();
	void Input(SDL_Event _event);

	void ChangeColour(int r, int g, int b, int a);

	std::vector<HL_Square*> aListofSquares;
	int X, Y, Num;
	float dirX, dirY;

};

