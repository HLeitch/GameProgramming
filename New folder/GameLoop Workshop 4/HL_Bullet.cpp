#include "HL_Bullet.h"
#include "HL_GameWorld.h"

HL_Bullet::HL_Bullet() :HL_GameObject()
{
	//Sprite information
	sprite = new SimpleSprite(theTextureManager->GetSprite("Content/Bullet.png")->pTexture);
	sprite->parent = this;

	_objectType = BULLET;

	impactSprite = new SimpleSprite(theTextureManager->GetTextureFromIndex(3));
	impactSprite->parent = this;
	Active = false;

	//Destination Rect Information
	myRect = new SDL_Rect;
	//BULLET TAKES POSITION FOR SPEEDY MOTION
	positionX = 500;
	positionY = 500;
	//
	myRect->w = 16;
	myRect->h = 36;
	

	myCollider = new CircleCollider(this, new HL_Vector2D(myRect->w / 2, myRect->h / 2), myRect->h / 2);
}



HL_Bullet::~HL_Bullet()
{

	
}

void HL_Bullet::Update()
{
	positionX = positionX+ (velocity.X * ((double) gTimer.deltaTime / 1000));
	positionY = positionY + (velocity.Y*((double) gTimer.deltaTime/1000));
	myRect->x = positionX;
	myRect->y = positionY;

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Bullet (%p) Moved to location(%lf, %lf)", this, positionX, positionY);
}



/// <summary>
/// Waking a bullet will shoot it in a direction. Give the unit vector of direction you'd like to shoot in
/// Without speed fires at 20 pps (pixels per second :)///
/// </summary>
/// <param name="direction"></param>
void HL_Bullet::Awake(HL_Vector2D* direction, HL_Vector2D* location, int rotation, int speed)
{
	Active = true;
	collisionCounter = 0;

	if ((direction->X > 1||direction->X < -1) && (direction->Y > 1|| direction->Y < -1))
	{
		SDL_LogInfo(SDL_LOG_CATEGORY_ERROR, "Bullet Tried to fire without unit vector, %p",this);
		return;
	}

	velocity.X = direction->X*speed;
	velocity.Y = direction->Y*speed;

	this->rotation = rotation;

	positionX = location->X;
	positionY = location->Y;

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Bullet (%p) spawned at location(%i, %i) with direction (%lf, %lf) and speed (%u)", this,myRect->x,myRect->y, direction->X,direction->Y, speed);

	delete direction;
	delete location;
}

void HL_Bullet::HasCollided(HL_Collider* otherCollider)
{
	collisionCounter += 1;

		Active = false;

		
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "BULLET Collided, Deactivated, %p", this);
	
}
