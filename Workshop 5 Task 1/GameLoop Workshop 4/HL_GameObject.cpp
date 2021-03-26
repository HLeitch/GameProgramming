#include "HL_GameObject.h"
#include "HL_GameWorld.h"

void HL_GameObject::Init()
{
	printf("Default Init called");
}

void HL_GameObject::Input(SDL_Event)
{
	printf("Default Input Called");
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
