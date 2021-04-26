//#include "stdafx.h"
#include "HL_SimpleSprite.h"
#include "HL_Timer.h"
#include "SDL_Image.h"	// we need this for texture loading function

// default constructor isn't needed as all member variables are given default values already

// constructor that takes X,Y position and width/height values for sprite (src Rect will be calculated from them based on current frame)
// X is the starting X position, Y is the starting Y position to draw on screen. Width and Height are the size of a single frame of the sprite
// todo: think if we need to add more data here? Should we have scale? Should we have an offset value?? (so the sprite is centered at X,Y)
SimpleSprite::SimpleSprite(int x, int y, int widthPixels, int heightPixels)
{
	frameWidthPixels = widthPixels;
	frameHeightPixels = heightPixels;
	frameIndex = 0;
	srcRect.x = frameIndex * frameWidthPixels;
	srcRect.y = 0;
	srcRect.w = frameWidthPixels;
	srcRect.h = frameHeightPixels;

	xscale = 3;
	yscale = 3;
}

// here you should safely handle any memory you allocated.. remember you are loading textures? Do they need cleaning up?
SimpleSprite::~SimpleSprite()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
	}
}

// render the sprite to the current renderer using the current X,Y positions based on the current FrameIndex we are at
// usually you'd calculate your X,Y and scaled width and height in update, here you'd use the SDL_Rect values you've calculated
// to call SDL_RenderCopy to actually do the rendering. See slides for info.
void SimpleSprite::render(SDL_Renderer* renderer)
{
	int srcx = frameWidthPixels* frameIndex;

	 srcRect = { srcx,0,frameWidthPixels,frameHeightPixels };

	 xscale = 8;
	 yscale = 8;

	//dest rectangle, where drawing to on window
	SDL_Rect dstRect = { x,y,frameWidthPixels*xscale,frameHeightPixels*yscale};

	

	dstRect.x = ((gTimer.totalTicksSinceStart / 10) % 1000);
	center->x = 0;
	center->y = 0;
	Flip = SDL_FLIP_HORIZONTAL;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect,angle,center,Flip);
}

// this function should handle the logic of choosing the "source rectangle" srcRect, easy version is to follow the modulo % math given in the slides
// but that results in only playing a single sequence. Far better to expand on this and create your own sprite class!
void SimpleSprite::update(int ticks)
{
	/*
	Here you need to update the frame index value, then calculate the source rectangle srcRect using the updated frame index
	*/
	
	animationTimer += gTimer.deltaTime;

	if (animationTimer > animationSpeed)
	{
		frameIndex++;
		animationTimer = 0;
		SDL_Log(" New frame ");

	}

	SDL_Log("TimeElapsed = %d", animationTimer);

	//source rectangle drawn from
	if ((frameIndex >= numberOfFrames) || (frameIndex < 0))
	{
		frameIndex = 0;
	}

}
// load the texture (see lecture slides), colour key is usually not required for PNG with alpha channel (RGBA images)
// the "colour key" is essentially the first pixel (top left of the image) and is considered transparent when we don't have alpha channels (RGB images)
// its a bit old school, but some sprite sheets come with no alpha, so this is the convention to draw them properly
// note we need to pass the current SDL Renderer pointer into this function so that image functions work correctly for texture creation
// Note: In the case of using a colour key, we will likely want to use IMG_Load and store a temporary SDL_Surface * so we can then use SDL_SetColorKey on that
// surface before calling SDL_CreateTextureFromSurface
// If we don't need colour keying, we can simply call IMG_LoadTexture
void SimpleSprite::load(SDL_Renderer* renderer, const char* path, bool bUseColourKey)
{
	/*
	Check if there is a colour key in use (bUseColourKey), if there is use IMG_Load etc.. if not, using IMG_LoadTexture
	Check out the SDL2_Image api reference for information on those..
	*/
	if (bUseColourKey)
	{
		SDL_Surface* mySurface = IMG_Load(path);
		if (mySurface == NULL)
		{
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Null Pointer returned while loading content/sprite.png. using IMG_Load");
		}
		else
		{
			SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "loaded sprite while loading content/sprite.png");
		}



		 texture = SDL_CreateTextureFromSurface(renderer, mySurface);
		if (texture == NULL)
		{
			SDL_Log("myTexture was null");
		}
		else
		{
			SDL_FreeSurface(mySurface);
			SDL_Log("myTexture was assigned properly");
		}
	}
	//no colour key needed
	else
	{
		texture = IMG_LoadTexture(renderer, path);
		if (texture == NULL)
		{
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Null Pointer returned while loading content/sprite.png. using IMG_LoadTexture");
		}
		else
		{
			SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "loaded sprite while loading content/sprite.png using IMG_LoadTexture");
		}

	}

}

// simple setter
void SimpleSprite::setNumberOfFrames(unsigned int framecount)
{
	numberOfFrames = framecount;
}
// simple setter
void SimpleSprite::setAnimationSpeed(unsigned int speed)
{
	animationSpeed = speed;
}