#include "HL_GameObject.h"
#include "HL_GameWorld.h"

// class HL_GameWorld;


void HL_GameObject::Init(int xpos, int ypos, int w, int h)
{
	myRect = new SDL_Rect();
	this->x = xpos;
	this->y = ypos;
	this->width = w;
	this->height = h;

	myRect->x = this->x;
	myRect->y = this->y;
	myRect->w = this->width;
	myRect->h = this->height;

	this->R = 0;
	this->G = 0;
	this->B = 255;

	

	

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "An object initialised- %s (%p)", _objectName.c_str(), this);

	


}

void HL_GameObject::Input(SDL_Event* _event)
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

			case SDLK_a:
			
				MOVE_LEFT= true;
				break;
			case SDLK_d:
				
				MOVE_RIGHT = true;
				break;
			}
		}
		if (_event->type == SDL_KEYUP && _event->key.repeat == NULL)
		{
			switch (_event->key.keysym.sym) {
			case SDLK_ESCAPE:

				break;
			
			case SDLK_a:
				
				MOVE_LEFT = false;
				break;
			case SDLK_d:
				
				MOVE_RIGHT = false;
				break;
			}
		}
	}
}

void HL_GameObject::Update()
{
	if (sprite != nullptr)
	{
		sprite->update(0);
	}
}

void HL_GameObject::Render(SDL_Renderer* theRenderer)
{
	SDL_SetRenderDrawColor(theRenderer, R, G, B, 255);

	//SDL_RenderFillRect(theRenderer, myRect);
	if (sprite != nullptr)
	{
		sprite->render(theRenderer);
	}
	//SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Rendered object: %s (%p)", _objectName.c_str(), this);

	
}

void HL_GameObject::HasCollided(HL_Collider* otherCollider)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_ERROR, "DEFAULT HasCollided() called %p", this);


}

HL_GameObject::HL_GameObject()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Default GameObject Constructor called (%p)", this);
	_objectName = "Default GameObject";
	theTextureManager = theTextureManager->GetInstance();
	sprite = new SimpleSprite("Heartbeat");
	sprite->parent = this;
	
}

HL_GameObject::~HL_GameObject()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"Default Destructor called(%p)",this);
	if (myCollider != nullptr)
	{
		delete myCollider;
	}
	//delete myRect;
	if (sprite != nullptr)
	{
		delete sprite;
	}
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
