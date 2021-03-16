#include "HL_SpaceInvaderRow.h"



void HL_SpaceInvaderRow::Update()
{

	int* screenWidth = new int(1000);
	int* screenHeight = new int(1000);



	if (moving)
	{
		for (HL_SpaceInvader* si : myInvaders)
		{
			si->myRect->x += speed;
		}
		myRect->x += speed;
	}

	if ((myRect->x +myRect->w > *screenWidth) || (myRect->x < 0))
	{
		for (HL_SpaceInvader* si : myInvaders)
		{
			si->myRect->y += 20;

		}
		myRect->y += 20;

		speed = -speed;
	}
}

void HL_SpaceInvaderRow::Render(SDL_Renderer* theRenderer)
{
	for (HL_SpaceInvader* si : myInvaders)
	{
		si->Render(theRenderer);

	}

}

HL_SpaceInvaderRow::HL_SpaceInvaderRow()
{
	myRect->x = 10;
	myRect->w = 600;

	myRect->y = 30;
	
	myRect->h = 60;

	myColour->r = 255; myColour->g = 255; myColour->b = 255; myColour->a = 255;


	int counter = 0;
	int position = 0;


	while (counter <= 8)
	{
		HL_SpaceInvader* anInvader = new HL_SpaceInvader();
		anInvader->myRect->x =  this->myRect->x + position;
		anInvader->myRect->y = this->myRect->y;

		counter++;
		position += 70;

		myInvaders.push_back(anInvader);

	}



}


