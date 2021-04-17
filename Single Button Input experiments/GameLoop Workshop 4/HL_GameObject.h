#pragma once
#include "SDL.h"
#include "HL_Vector2D.h"
#include <iostream>
class HL_GameWorld;

/// <summary>
/// Class which can render a rect on the screen.
/// </summary>
class HL_GameObject
{
public:

	int x, y, height, width, R, G, B;

	virtual void Init(int xpos, int ypos, int w, int h);
	virtual void Input(SDL_Event);
	virtual void Update();
	virtual void Render(SDL_Renderer* theRenderer);

	HL_GameObject();
	virtual ~HL_GameObject();

	void SetColour(int newR, int newG, int newB);
	bool CopyColour(const HL_GameObject& otherGameObject);
	bool display = true;

	bool MOVE_LEFT = false;
	bool MOVE_RIGHT = false;

	HL_GameWorld* parent;

	SDL_Rect* myRect;
	HL_Vector2D velocity;
private:

};

