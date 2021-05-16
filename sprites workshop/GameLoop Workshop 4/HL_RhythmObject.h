#pragma once
#include "HL_GameObject.h"
#include "HL_SimpleSprite.h"
class HL_RhythmObject :
    public HL_GameObject
{
public:
    HL_RhythmObject();

    void Input(SDL_Event _event);

    void Input();


    
    bool active;

    bool pressed = false;
    
    

};

