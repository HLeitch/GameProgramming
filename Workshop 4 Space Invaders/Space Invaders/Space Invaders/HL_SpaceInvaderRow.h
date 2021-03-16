#pragma once
#include "HL_Rectangle.h"
#include "SDL.h"
#include "HL_SpaceInvader.h"
#include <Vector>


class HL_SpaceInvaderRow :
    public HL_Rectangle
{
public:
    int speed = 5;

    std::vector<HL_SpaceInvader*> myInvaders;

    void Init();
    void Update();
    void Render(SDL_Renderer* theRenderer);
    






    HL_SpaceInvaderRow();

};

