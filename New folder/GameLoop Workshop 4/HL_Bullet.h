#pragma once
#include "HL_GameObject.h"
class HL_Bullet :
    public HL_GameObject
{

public:
    HL_Bullet();
    
    ~HL_Bullet();


    void Update();

    void Awake(HL_Vector2D* direction, HL_Vector2D* location, int rotation, int speed = 20);

    SimpleSprite* impactSprite = nullptr;

    void HasCollided(HL_Collider* otherCollider);

    int collisionCounter = 0;
    

    double positionX = 0;
    double positionY = 0;
};

