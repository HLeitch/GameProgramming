#include "HL_RhythmObject.h"

HL_RhythmObject::HL_RhythmObject() :HL_GameObject()
{
	active = false;


	sprite = new SimpleSprite("Heartbeat");
	sprite->parent = this;

}
void HL_RhythmObject::Input(SDL_Event* _event)
{

	if (_event->type == SDL_USEREVENT)
	{
		if (_event->user.code == 0)
		{
			this->sprite->currentAnimationIndex = 0;

		}

	}
}






