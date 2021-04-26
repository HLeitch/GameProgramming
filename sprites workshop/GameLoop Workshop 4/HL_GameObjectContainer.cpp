#include "HL_GameObjectContainer.h"


HL_GameObjectContainer::HL_GameObjectContainer()
{
}


void HL_GameObjectContainer::Init(int eY, int eX, float eDirX, float eDirY, int eNum)
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

void HL_GameObjectContainer::Add(int x, int y)
{
	HL_GameObject* aGameObject = new HL_GameObject();
	aGameObject->Init(x, y, 20, 20);
	this->aListofGameObjects.push_back(aGameObject);

}

void HL_GameObjectContainer::Render(SDL_Renderer* aRenderer)
{
	for (HL_GameObject* square : aListofGameObjects)
	{
		square->Render(aRenderer);
	}
}

void HL_GameObjectContainer::Update()
{
	{
		for (HL_GameObject* square : aListofGameObjects)
		{
			//square->myRect->x++;
		}
	}
}

void HL_GameObjectContainer::Input(SDL_Event _event)
{
	for (HL_GameObject* anIterator : aListofGameObjects)
	{
		anIterator->Input(_event);
	}

	if (_event.key.keysym.sym == SDLK_CAPSLOCK)
	{
		
	}
}

void HL_GameObjectContainer::ChangeColour(int r, int g, int b)
{
	for (HL_GameObject* square : aListofGameObjects)
	{
		square->R = r;
		square->G = g;
		square->B = b;
	


	}

}

HL_GameObjectContainer::~HL_GameObjectContainer() {
	for (HL_GameObject* square : aListofGameObjects)
	{
		delete square;
	}
}
