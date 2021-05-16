#pragma once
#include "HL_GameObject.h"
class HL_Enemy :
    public HL_GameObject
{

public:
    HL_Enemy();
    ~HL_Enemy();

    void Render(SDL_Renderer* renderer);
    void Input(SDL_Event _event);

    void Update();

    SimpleSprite* _StationarySprite;

    void Awake(double x, double y);

    void HasCollided(HL_Collider* otherCollider);

    int GetRotation();
    /// <summary>
    /// sets the rotation of this object to a value between 0 and 365
    /// </summary>
    /// <param name="value"></param>
    void SetRotation(int value);

private:
    float maxSpeed = 30;

};

