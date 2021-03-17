#include "HL_Rectangle.h"
#include "HL_GameWorld.h"

void HL_Rectangle::Init()
{

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
	case 'w': {printf("Square: W is pressed \n"); 
		
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

	SDL_RenderDrawRect(theRenderer, myRect);
}

HL_Rectangle::HL_Rectangle(int x, int y, int width, int height)
{
	
	xPos = x;
		yPos = y;
		this->width = width;
		this->height = height;

		myRect = new SDL_Rect();
		Init();
		/*myRect->x = xPos;
		myRect->y = yPos;
		myRect->w = width;
		myRect->h = height;

		myColour->r = 255; myColour->g = 255; myColour->b = 255; myColour->a = 255;*/

		
	
}

HL_Rectangle::~HL_Rectangle()
{
}


