#include "HL_BulletContainer.h"
#include "HL_Player.h"

HL_BulletContainer::HL_BulletContainer()
{
	int counter = 0;
	while (counter < maxNumberOfBullets)
	{
		HL_Bullet* bull = new HL_Bullet();
		bullets.push_back(bull);
		counter++;
	}

}

void HL_BulletContainer::Fire(HL_Player* player,HL_Vector2D* direction, int destRotation)
{
	HL_Bullet* toFire = nullptr;
	
		for (HL_Bullet* bull : bullets)
		{
			if (!bull->Active)
			{
				toFire = bull;
				break;
			}
			
			else
			{
				continue;
				
			}
			
			
		}
		if (toFire == nullptr)
		{
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Tried to fire, but no inactive bullets remained");
		}
		else
		{
			toFire->Awake(direction,player->findMidpoint(),destRotation,200);
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Fired Bullet from container! %p",toFire);
		}
	

}

void HL_BulletContainer::Render(SDL_Renderer* renderer)
{
	for (HL_Bullet* bull : bullets)
	{
		if (bull->Active)
		{
			bull->Render(renderer);
		}
	}
}

void HL_BulletContainer::Update()
{
	for (HL_Bullet* bull : bullets)
	{
		if (bull->Active)
		{
			bull->Update();
		}
	}
}

HL_BulletContainer::~HL_BulletContainer()
{
	for (HL_Bullet* bull : bullets)
	{
		delete bull;
		bull = nullptr;
	}
}
