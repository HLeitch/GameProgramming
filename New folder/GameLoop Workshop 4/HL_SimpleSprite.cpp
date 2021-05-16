//#include "stdafx.h"
#include "HL_SimpleSprite.h"
#include "HL_GameObject.h"

// default constructor isn't needed as all member variables are given default values already

SimpleSprite::SimpleSprite(int x, int y, int widthPixels, int heightPixels)
{
}

SimpleSprite::SimpleSprite(std::string sequence = "")
{
	animated = true;
	theTextureManager = TextureManager::GetInstance();

	if (sequence != "")
	{

		animation = theTextureManager->GetSequence(sequence);

		if(animation != nullptr) SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Animation Loaded to Sprite Object %p, (animation: %s, %p)", this, animation->name.c_str(),animation);
		else SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Animation not Loaded to sprite (%p)", this);
	}
}

SimpleSprite::SimpleSprite(SDL_Texture* texture)
{
	animated = false;
	this->texture = texture;
	if (texture == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Texture not Loaded (%p, texure Pointer %p)", this, texture);
	}

	else
	{
		SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Single Texture Loaded to Sprite Object %p, (texture: %p)", this, texture);
	}

}

SimpleSprite::SimpleSprite(const TexInfo_t* texinfo)
{
	animated = false;
	this->texture = texinfo->pTexture;
	dstRect = nullptr;

	if (texture == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Texture not Loaded (%p, texure Pointer %p)", this, texture);
	}

	else
	{
		SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Single Texture Loaded to Sprite Object (from texinfo object) Sprite: %p, texture: %p", this, texture);
	}
}

// here you should safely handle any memory you allocated.. remember you are loading textures? Do they need cleaning up?
SimpleSprite::~SimpleSprite()
{
	/*SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "SPRITE BEING DELETED %p. CONTAINING %s texture (%p)", this, this->currentFrame->name, this->currentFrame);
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
	}*/
}

// render the sprite to the current renderer using the current X,Y positions based on the current FrameIndex we are at
// usually you'd calculate your X,Y and scaled width and height in update, here you'd use the SDL_Rect values you've calculated
// to call SDL_RenderCopy to actually do the rendering. See slides for info.
void SimpleSprite::render(SDL_Renderer* renderer)
{
	if (active && parent)
	{
		dstRect = parent->myRect;
		angle = parent->rotation;

		if(animated)
		SDL_RenderCopyEx(renderer, texture,&currentFrame->srcRect , dstRect,angle,NULL,SDL_FLIP_VERTICAL);
		else
		{
			SDL_RenderCopyEx(renderer, texture, NULL, dstRect, angle, NULL, SDL_FLIP_NONE);
		}
	}
}

// this function should handle the logic of choosing the "source rectangle" srcRect, easy version is to follow the modulo % math given in the slides
// but that results in only playing a single sequence. Far better to expand on this and create your own sprite class!
void SimpleSprite::update(int ticks)
{
	/*
	Here you need to update the frame index value, then calculate the source rectangle srcRect using the updated frame index
	*/
	//SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "simplesprite update called");

	if (animation && animated)
	{
		timeSinceAnimationChange += gTimer.deltaTime;
		if (timeSinceAnimationChange > animation->playbackrate)
		{
			timeSinceAnimationChange = 0;
			currentAnimationIndex++;
			if (currentAnimationIndex >= animation->mFrameIndices.size())
			{
				currentAnimationIndex = 2;
			}
			currentFrame = theTextureManager->GetFrame(animation->mFrameIndices[currentAnimationIndex]);
			texture = theTextureManager->GetTextureFromIndex(currentFrame->textureindex);
		}
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

