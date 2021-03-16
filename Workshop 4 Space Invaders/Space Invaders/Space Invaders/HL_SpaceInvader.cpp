#include "HL_SpaceInvader.h"

void HL_SpaceInvader::Update()
{
	//NO UPDATE IMPLIMENTED


}

void HL_SpaceInvader::Move(int amount)
{
	myRect->x += amount;

}

HL_SpaceInvader::HL_SpaceInvader()
{
	myRect->w = 40;
	myRect->h = 40;

	myColour->b = 0;
	myColour->g = 0;
	myColour->r = 255;
	myColour->a = 255;


}
