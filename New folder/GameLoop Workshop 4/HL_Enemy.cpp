#include "HL_Enemy.h"
#include "HL_GameWorld.h"
HL_Enemy::HL_Enemy()
{
	_StationarySprite = new SimpleSprite("EnemyRunning");
	_StationarySprite->parent = this;
	
	//Destination Rect Information
	myRect = new SDL_Rect;
	myRect->x = 5;
	myRect->y = 200;
	myRect->w = 80;
	myRect->h = 80;

	myCollider = new CircleCollider(this, new HL_Vector2D(myRect->w / 2, myRect->h / 2), myRect->h / 2);

	_objectType = ENEMY;

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Enemy Created, %p", this);

	Awake(900, 200);
}

HL_Enemy::~HL_Enemy()
{
}

void HL_Enemy::Render(SDL_Renderer* renderer)
{
	_StationarySprite->render(renderer);
}

void HL_Enemy::Input(SDL_Event _event)
{
}

void HL_Enemy::Update()
{ 

	if (Active) {
		realPosition.X += (velocity.X * ((double)gTimer.deltaTime / 1000));
		realPosition.Y += (velocity.Y * ((double)gTimer.deltaTime / 1000));

		myRect->x = realPosition.X;
		myRect->y = realPosition.Y;

		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Enemy Moved to (%lf,%lf) %p", realPosition.X, realPosition.Y, this);

		_StationarySprite->update(0);
	}
}

void HL_Enemy::Awake(double x, double y)
{
	Active = true;
	realPosition.X = x;
	realPosition.Y = y;
	HL_Vector2D tempvect = HL_Vector2D(x, y);
	HL_Vector2D* center = new HL_Vector2D(GAME_WINDOW_WIDTH/2, GAME_WINDOW_HEIGHT/2);

	//double distance = tempvect.distance(center);
	//HL_Vector2D unitv = ()

	velocity.X = ((GAME_WINDOW_WIDTH / 2) - x) / tempvect.distance(center) * maxSpeed;
	velocity.Y = ((GAME_WINDOW_HEIGHT / 2) - y) / tempvect.distance(center) * maxSpeed;
}

void HL_Enemy::HasCollided(HL_Collider* otherCollider)
{
	if (otherCollider->parent->_objectType == BULLET)
	{
		this->Active = false;

		SDL_Event userEvent;
		userEvent.type = SDL_USEREVENT;
		userEvent.user.code = ENEMY_DIED_EVENT;
		SDL_PushEvent(&userEvent);
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Enemy Died, %p", this);
	}
}

int HL_Enemy::GetRotation()
{
	return 0;
}

void HL_Enemy::SetRotation(int value)
{
}
