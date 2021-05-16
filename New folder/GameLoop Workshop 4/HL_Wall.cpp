#include "HL_Wall.h"
#include "HL_GameWorld.h"
HL_Wall::HL_Wall(int x, int y, int w, int h): HL_GameObject()
{
	_objectName = "wall";
	sprite = nullptr;

	Init(x, y, w, h);
	myCollider = new SquareCollider(this, x, y, w, h);
	_objectType = WALL;
	_objectName = "Wall";

	Active = true;
}

void HL_Wall::HasCollided(HL_Collider* otherCollider)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_ASSERT, "Wall involved in collision %p, Other Collider %p", this, otherCollider);


	if (otherCollider->parent->x > this->x)
	{
		otherCollider->parent->velocity.X = -otherCollider->parent->velocity.X;
		
	}
	if (otherCollider->parent->x < this->x)
	{
		otherCollider->parent->velocity.X = -otherCollider->parent->velocity.X;
	}
	if (otherCollider->parent->y > this->y)
	{
		otherCollider->parent->velocity.Y = -otherCollider->parent->velocity.Y;
	}
	if (otherCollider->parent->y < this->y)
	{
		otherCollider->parent->velocity.Y = -otherCollider->parent->velocity.Y;
	}



}

void HL_Wall::Render(SDL_Renderer* renderer )
{
	SDL_RenderFillRect(renderer, myRect);
}
