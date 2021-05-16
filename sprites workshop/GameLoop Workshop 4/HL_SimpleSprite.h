#pragma once
#include "SDL.h"
#include "HL_Timer.h"
#include "SDL_Image.h"	// we need this for texture loading function
#include "TextureManager.h"
#include "HL_GameObject.h"


// "Simple" sprite class example outline - You need to complete the functions to make this work. This is intended to get you started, but needs a lot of
// work to make it fit for purpose. Get this working and then expand on it to make a proper sprite class for yourself.
// See the .cpp file for comments on what each function does
class SimpleSprite
{
public:
	SimpleSprite(int x, int y, int widthPixels, int heightPixels);
	SimpleSprite(std::string sequence);
	~SimpleSprite();

	// you might need to rename these functions to work with your own code.. don't forget to update the CPP file too!
	void render(SDL_Renderer* renderer);
	void update(int ticks);
	void load(SDL_Renderer* renderer, const char* path, bool bUseColourKey = false);

	unsigned int currentAnimationIndex = 0;
	bool active = true;

	//rotation angle 
	double angle = 30;
	//point around which rotated
	SDL_Point* center = new SDL_Point;

	//Flipped? default = NONE
	SDL_RendererFlip Flip = SDL_FLIP_NONE;
	
	HL_GameObject* parent;

protected:

	TextureManager* theTextureManager = NULL;
	SDL_Texture* texture = nullptr;	// pointer to an SDL_Texture, always initialize your pointers to either NULL or nullptr
	SDL_Rect* dstRect;		
	
	// this is the source rectangle where we will copy the sprite from within the texture

	const SpriteSequence* animation = NULL;
	const SpriteFrame* currentFrame = NULL;

	unsigned int timeSinceAnimationChange = 0;

	

	
	unsigned int animationTimer = 0;	// how long since the last frame?
		// which frame are we currently on?

	
};
