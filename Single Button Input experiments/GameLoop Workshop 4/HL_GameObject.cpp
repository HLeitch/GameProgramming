#include "HL_GameObject.h"
#include "HL_GameWorld.h"


void HL_GameObject::Init(int xpos, int ypos, int w, int h)
{
	this->x = xpos;
	this->y = ypos;
	this->width = w;
	this->height = h;

	this->R = 0;
	this->G = 0;
	this->B = 0;
}

void HL_GameObject::Input(SDL_Event)
{
	{
		if (_event.type == SDL_QUIT)
		{//do nothing
		}
		if (_event.type == SDL_KEYDOWN && _event.key.repeat == NULL)
		{
			switch (_event.key.keysym.sym) {
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
				MOVE_LEFT= true;
				break;
			case SDLK_d:
				printf("Square: MOVING RIGHT\n");
				MOVE_RIGHT = true;
				break;
			}
		}
		if (_event.type == SDL_KEYUP && _event.key.repeat == NULL)
		{
			switch (_event.key.keysym.sym) {
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

void HL_GameObject::Update()
{
	printf("Default Update Called");
}

void HL_GameObject::Render(SDL_Renderer* theRenderer)
{
	printf("Default Render() function called");
}

HL_GameObject::HL_GameObject()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Default GameObject Constructor called (%p)", this);
}

HL_GameObject::~HL_GameObject()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"Default Destructor called(%p)",this);
}

void HL_GameObject::SetColour(int newR, int newG, int newB)
{
	this->R = newR;
	this->G = newG;
	this->B = newB;
}

bool HL_GameObject::CopyColour(const HL_GameObject& otherGameObject)
{
	if (&otherGameObject == this)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "GameObject tried to copy it's own colour (%p)", this);
		return false;
	}
	else
	{
		this->SetColour(otherGameObject.R, otherGameObject.G, otherGameObject.B);
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "GameObject copied colour from another Gameobject. (%p) copied from (%p)", this, &otherGameObject);

		return true;
	}
	
}
