#pragma once
#include "HL_GameObject.h"
class HL_RhythmObject :
    public HL_GameObject
{
public:
    HL_RhythmObject();

    void Render(SDL_Renderer* renderer);
    
    bool active;

    bool pressed = false;


};

