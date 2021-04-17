#include "HL_RhythmObjectContainer.h"



HL_RhythmObjectContainer::HL_RhythmObjectContainer()
{
}


void HL_RhythmObjectContainer::Init(int eX, int eY, float eDirX, float eDirY, int eNum)
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

void HL_RhythmObjectContainer::Add(int x, int y)
{
	HL_RhythmObject* aRhythmObject = new HL_RhythmObject();
	aRhythmObject->Init(x, y, 40, 40);
	this->aListofRhythmObjects.push_back(aRhythmObject);

}

void HL_RhythmObjectContainer::Render(SDL_Renderer* aRenderer)
{
	for (HL_RhythmObject* square : aListofRhythmObjects)
	{
		square->Render(aRenderer);
	}
}

void HL_RhythmObjectContainer::Update()
{
	{
		for (HL_RhythmObject* square : aListofRhythmObjects)
		{
			//square->myRect->x++;
		}
	}
}

void HL_RhythmObjectContainer::Input(SDL_Event _event)
{
	for (HL_RhythmObject* anIterator : aListofRhythmObjects)
	{
		anIterator->Input(_event);
	}

	if (_event.type == SDL_KEYDOWN && _event.key.repeat == NULL)
	{
		switch (_event.key.keysym.sym) {

		case SDLK_SPACE:

			if (aListofRhythmObjects[roundCounter]->active = true)
			{
				aListofRhythmObjects[roundCounter]->pressed = true;
			}
			else
			{
				///FAILED IMPLIMENTATIONi
			}
			roundCounter++;


		}
	}
}

void HL_RhythmObjectContainer::ChangeColour(int r, int g, int b)
{
	for (HL_RhythmObject* square : aListofRhythmObjects)
	{
		square->R = r;
		square->G = g;
		square->B = b;



	}

}

int HL_RhythmObjectContainer::PressedObjects()
{
	int counter = 0;
	for (HL_RhythmObject* anIterator : aListofRhythmObjects)
	{
		if ((anIterator->pressed == true))
		{
			counter++;
		}
	}
	return counter;
}

HL_RhythmObjectContainer::~HL_RhythmObjectContainer() {
	for (HL_RhythmObject* square : aListofRhythmObjects)
	{
		delete square;
	}
}
