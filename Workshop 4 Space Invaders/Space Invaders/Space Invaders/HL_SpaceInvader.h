#pragma once
#include "HL_Rectangle.h"
class HL_SpaceInvader :
    public HL_Rectangle
{
public:
    void Update();
    void Move(int);


    HL_SpaceInvader();

};

