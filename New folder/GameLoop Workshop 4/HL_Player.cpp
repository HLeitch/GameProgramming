#include "HL_Player.h"
#include "HL_GameWorld.h"
HL_Player::HL_Player():HL_GameObject()
{
	//Sprite information
	 _StationarySprite =  new SimpleSprite(theTextureManager->GetSprite("Content/PlayerStand.png"));
	 _StationarySprite->parent = this;


	 //Destination Rect Information
	 myRect = new SDL_Rect;
	 myRect->x = 5;
	 myRect->y = 600;
	 myRect->w = 249;
	 myRect->h = 106;

	 

	 realPosition.X = myRect->x;
	 realPosition.Y = myRect->y;
	 _objectType = PLAYER;

	 myCollider = new CircleCollider(this, findMidpoint(), myRect->h / 2);
}

HL_Vector2D* HL_Player::findMidpoint()
{
	x = (myRect->x + (myRect->w / 2));
	y = (myRect->y + (myRect->h / 2));

	return new HL_Vector2D(x, y);
}

HL_Player::~HL_Player()
{
	delete _StationarySprite;
	delete myRect;
	
}

void HL_Player::Render(SDL_Renderer* renderer)
{
	_StationarySprite->render(renderer);

}



void HL_Player::Input(SDL_Event* _event)
{
	//Key down events
	
		if (_event->type == SDL_KEYDOWN && _event->key.repeat == NULL)
		{
			switch (_event->key.keysym.sym) {
			case SDLK_ESCAPE:

				break;

			case SDLK_a:
			MOVE_LEFT = true;
				break;
			case SDLK_d:

				MOVE_RIGHT = true;
				break;
			case SDLK_w:

				MOVE_UP = true;
				break;
			case SDLK_s:
				MOVE_DOWN = true;
				break;


			case SDLK_j:
				ROTATE_CW = true;
				break;

			case SDLK_k:
				ROTATE_ACW = true;
				break;
			case SDLK_SPACE:
				FireBullets();
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

			case SDLK_w:

				MOVE_UP = false;
				break;
			case SDLK_s:
				MOVE_DOWN = false;
				break;


			case SDLK_j:
				ROTATE_CW = false;
				break;
			
			case SDLK_k:
					ROTATE_ACW = false;
					break;
			}
		}
	

		if (_event->type == SDL_USEREVENT)
		{
			if (_event->user.code == PLAYER_DAMAGED_EVENT)
			{
				SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Player Damaged Event Picked up in Player Input Loop!! %p", &_event);
			}
		}


}

void HL_Player::FireBullets()
{
	
	/// Direction the right bullet is fired relative to the world = player rotation + 90 since were going horizontal1
	double gXdirection = SDL_cos((rotation*(M_PI/180)));
	double gYdirection = SDL_sin((rotation*(M_PI/180)));

	HL_Vector2D* dir = new HL_Vector2D(gXdirection, gYdirection);
	HL_Vector2D* Ldir = new HL_Vector2D(-gXdirection, -gYdirection);

	myBulletContainer->Fire(this, dir, rotation+90);
	SDL_LogInfo(SDL_LOG_CATEGORY_ASSERT, "Right Bullet Fired in direction, (%lf,%lf)", gXdirection, gYdirection);

	myBulletContainer->Fire(this, Ldir, rotation-90);
	SDL_LogInfo(SDL_LOG_CATEGORY_ASSERT, "left Bullet Fired in direction, (%lf,%lf)", -gXdirection, -gYdirection);
}

void HL_Player::Update()
{

	float dirx = 0;
		float diry = 0;
	
		if (MOVE_UP)
		{
			diry -= 1;
		}
		if (MOVE_DOWN)
		{
			diry += 1;
		}
		if (MOVE_LEFT)
		{
			dirx -= 1;
		}
		if (MOVE_RIGHT)
		{
			dirx += 1;
		}

		if (dirx != 0 && diry != 0)
		{
			velocity.X = sqrt((maxSpeed*maxSpeed) / 2) * dirx;
			velocity.Y = sqrt((maxSpeed * maxSpeed) / 2) * diry;

			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Player moving (%i,%i)", velocity.X, velocity.Y);
		}
		else
		{
			velocity.X = maxSpeed * dirx;
			velocity.Y = maxSpeed * diry;
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Player moving (%i,%i)", velocity.X, velocity.Y);
		}


		realPosition.X += velocity.X;
		realPosition.Y += velocity.Y;
		myRect->x = realPosition.X;
		myRect->y = realPosition.Y;

		if (ROTATE_CW)
		{
			SetRotation(GetRotation() + rotationalSpeed);

		}
		if (ROTATE_ACW)
		{
			SetRotation(GetRotation() - rotationalSpeed);
		}


}


void HL_Player::HasCollided(HL_Collider* otherCollider)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Player Collided With an object %p with other %p", this,otherCollider->parent);

	if (otherCollider->parent->_objectType == ENEMY)
	{
		HL_Event type = PLAYER_DAMAGED_EVENT;

		SDL_Event userEvent;
		userEvent.type = SDL_USEREVENT;
		userEvent.user.code = type;

		


		if (SDL_PushEvent(&userEvent)) {
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "PLAYER DEATH EVENT PUSHED");
		}
	}
	
}

int HL_Player::GetRotation()
{
	return rotation;
}

void HL_Player::SetRotation(int value)
{
	int result = value % 365;

	this->rotation = result;
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Player rotation now at: %i", this->rotation);
}


