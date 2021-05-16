#include "HL_Square.h"

HL_Square::HL_Square()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Square Constructed with Param (%p)", this);

	myRect = new SDL_Rect;
}

HL_Square::~HL_Square()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Square Destroyed (%p)", this);

}

void HL_Square::Init(int xpos, int ypos, int wid, int hig)
{
	HL_Rectangle* rect1 = new HL_Rectangle(); rect1->Init(xpos, ypos, wid / 2, hig / 2);
	HL_Rectangle* rect2 = new HL_Rectangle(); rect2->Init((xpos + wid / 2), ypos, wid / 2, hig / 2);
	HL_Rectangle* rect3 = new HL_Rectangle(); rect3->Init(xpos, ypos + wid / 2, wid / 2, hig / 2);
	HL_Rectangle* rect4 = new HL_Rectangle(); rect4->Init(xpos + wid / 2, ypos + wid / 2, wid / 2, hig / 2);

	
	myRect->x = xpos - 5;
	myRect->y = ypos - 5;
	myRect->w = wid + 10;
	myRect->h = hig + 10;
	this->myColour->r = 255; this->myColour->g = 255; this->myColour->b = 255; this->myColour->a = 255;


	rect2->myColour->r = 0; rect3->myColour->g = 0; rect4->myColour->r = 0; rect4->myColour->b = 0;

	myRects.push_back(rect1); myRects.push_back(rect2); myRects.push_back(rect3); myRects.push_back(rect4);

}

void HL_Square::Render(SDL_Renderer* theRenderer)
{
	SDL_SetRenderDrawColor(theRenderer, myColour->r, myColour->g, myColour->b, myColour->a);

	SDL_RenderDrawRect(theRenderer, myRect);
	for(HL_Rectangle* r : myRects)
	{
		r->Render(theRenderer);

	}

}

void HL_Square::Update()
{
	if (right)
	{
		Move(1,0);

	}
	if (left)
	{
		Move(-1,0);
	}
	if (up)
	{
		Move(0,-1);
	}
	if (down)
	{
		Move(0,1);
	}


}

void HL_Square::Input(SDL_Event* _event)
{

	{
		if (_event->type == SDL_QUIT)
		{//do nothing
		}
		if (_event->type == SDL_KEYDOWN && _event->key.repeat == NULL)
		{
			switch (_event->key.keysym.sym) {
			case SDLK_ESCAPE:
				
				break;
			case SDLK_w:
				printf("Square: MOVING UP \n");
				up = true;
				break;
			case SDLK_s:
				printf("Square: MOVING DOWN\n");
				down = true;
				break;
			case SDLK_a:
				printf("Square: Moving LEFT\n");
				left = true;
				break;
			case SDLK_d:
				printf("Square: MOVING RIGHT\n");
				right = true;
				break;
			}
		}
		if (_event->type == SDL_KEYUP && _event->key.repeat == NULL)
		{
			switch (_event->key.keysym.sym) {
			case SDLK_ESCAPE:

				break;
			case SDLK_w:
				printf("Square: NO LONGER MOVING UP \n");
				up = false;
				break;
			case SDLK_s:
				printf("Square: NO LONGER MOVING DOWN\n");
				down = false;
				break;
			case SDLK_a:
				printf("Square: NO LONGER Moving LEFT\n");
				left = false;
				break;
			case SDLK_d:
				printf("Square: NO LONGER MOVING RIGHT\n");
				right = false;
				break;
			}
		}
	}

	
}

void HL_Square::Move(int hori, int vert)
{

	for (HL_Rectangle* r : myRects)
	{
		r->myRect->x += (hori * speed);
		r->myRect->y += (vert * speed);

	}



}

bool HL_Square::CopyColour(const HL_Square& otherSquare)
{
	if (&otherSquare == this)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Square tried to copy it's own colour (%p)", this);
		return false;
	}
	else
	{
		this->myColour = otherSquare.myColour;
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Square copied colour from another square. (%p) copied from (%p)", this,&otherSquare);

		return true;
	}
}
