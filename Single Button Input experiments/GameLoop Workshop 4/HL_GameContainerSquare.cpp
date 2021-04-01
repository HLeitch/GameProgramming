#include "HL_GameContainerSquare.h"


HL_GameContainerSquare::HL_GameContainerSquare()
{
}


void HL_GameContainerSquare::Init(int eY, int eX, float eDirX, float eDirY, int eNum)
{
	X = eX;
	Y = eY;
	dirX = eDirX;
	dirY = eDirY;
	Num = eNum;
	for (int i = 0; i < Num; i++)
	{
		int PosX = X + (i * (dirX * 10));
		int PosY = Y + (i * (dirY * 10));
		Add(PosX, PosY);
	}
}

void HL_GameContainerSquare::Add(int x, int y)
{
	HL_Square* aSquare = new HL_Square();
	aSquare->Init(x, y, 20, 20);
	this->aListofSquares.push_back(aSquare);

}

void HL_GameContainerSquare::Render(SDL_Renderer* aRenderer)
{
	for (HL_Square* square : aListofSquares)
	{
		square->Render(aRenderer);
	}
}

void HL_GameContainerSquare::Update()
{
	{
		for (HL_Square* square : aListofSquares)
		{
			//square->myRect->x++;
		}
	}
}

void HL_GameContainerSquare::Input(SDL_Event _event)
{
	for (HL_Square* anIterator : aListofSquares)
	{
		anIterator->Input(_event);
	}

	if (_event.key.keysym.sym == SDLK_CAPSLOCK)
	{
		
	}
}

void HL_GameContainerSquare::ChangeColour(int r, int g, int b, int a)
{
	for (HL_Square* square : aListofSquares)
	{
		square->myColour->r = r;
		square->myColour->g = g;
		square->myColour->b = b;
		square->myColour->a = a;


	}

}

HL_GameContainerSquare::~HL_GameContainerSquare() {
	for (HL_Square* square : aListofSquares)
	{
		delete square;
	}
}
