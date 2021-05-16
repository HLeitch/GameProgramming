#pragma once
#include "HL_GameObject.h"
class HL_Wall :
    public HL_GameObject
{

public:
    HL_Wall(int x, int y, int w, int h);
    void HasCollided(HL_Collider* otherObject) override;

    void Render(SDL_Renderer*);


};

