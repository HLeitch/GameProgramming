#pragma once
#include "HL_GameObject.h"
#include "HL_SimpleSprite.h"
#include "HL_BulletContainer.h"

class HL_Player :
    public HL_GameObject
{

public:
    HL_Player();

    ~HL_Player();

   void Render(SDL_Renderer* renderer);
   void Input(SDL_Event* _event);

   void FireBullets();

   void Update();
    
    SimpleSprite* _StationarySprite = nullptr;

    HL_BulletContainer* myBulletContainer = nullptr;

    void HasCollided(HL_Collider* otherCollider);

    HL_Vector2D* findMidpoint();

    int GetRotation();
    /// <summary>
    /// sets the rotation of this object to a value between 0 and 365
    /// </summary>
    /// <param name="value"></param>
    void SetRotation(int value);
 

private:
    float maxSpeed = 4;
    int acceleration = 1;
    int rotationalSpeed = 6;
   
    bool ROTATE_CW = false;
    bool ROTATE_ACW = false;

    HL_Vector2D RightBulletDirection = HL_Vector2D(1,0);
    HL_Vector2D LeftBulletDirection = HL_Vector2D(-1, 0);


};

