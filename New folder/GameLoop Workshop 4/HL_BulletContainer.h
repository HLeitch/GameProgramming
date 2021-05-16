#pragma once
#include "HL_GameObjectContainer.h"
#include "HL_Bullet.h"

class HL_Player;
class HL_BulletContainer :
    public HL_GameObjectContainer
{
public:
    HL_BulletContainer();

    void Fire(HL_Player* player, HL_Vector2D* direction, int destRotation);

    std::vector<HL_Bullet*> bullets;

    int maxNumberOfBullets = 6;



    void Render(SDL_Renderer* renderer);

    void Update();

    ~HL_BulletContainer();

};

