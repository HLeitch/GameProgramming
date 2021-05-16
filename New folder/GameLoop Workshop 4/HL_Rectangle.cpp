#include "HL_Rectangle.h"
#include "HL_GameWorld.h"

void HL_Rectangle::Init(int xPos, int yPos, int width, int height)
{
	

	myRect = new SDL_Rect();
	myRect->x = xPos;
	myRect->y = yPos;
	myRect->w = width;
	myRect->h = height;

	myColour->r = 255; myColour->g = 255; myColour->b = 255; myColour->a = 255;

	
}

void HL_Rectangle::Input(int whichKey)
{
	switch (whichKey)
	{
	case 'w': {printf("GameObject: W is pressed \n"); 
		
		moving = false;

		break; }
		
	}
}

void HL_Rectangle::Update()
{
	int* screenWidth = new int(1000);
	int* screenHeight = new int(1000);

	

	if (moving) { myRect->x += speed; }

	if ((myRect->x > *screenWidth) || (myRect->x < 0))
	{
		speed = -speed;
	}
}

void HL_Rectangle::Render(SDL_Renderer* theRenderer)
{	
	SDL_SetRenderDrawColor(theRenderer, myColour->r,myColour->g,myColour->b,myColour->a);
	sprite->render(theRenderer);

	SDL_RenderFillRect(theRenderer, myRect);
}

HL_Rectangle::HL_Rectangle()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Rectangle Constructed with Param (%p)", this);

		
		/*myRect->x = xPos;
		myRect->y = yPos;
		myRect->w = width;
		myRect->h = height;

		myColour->r = 255; myColour->g = 255; myColour->b = 255; myColour->a = 255;*/

		
	
}

HL_Rectangle::~HL_Rectangle()
{
}


