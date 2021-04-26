#pragma once
#include "HL_GameObject.h"
#include "HL_Rectangle.h"

#include <vector>



class HL_Square :
    public HL_GameObject
{
private:
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;

    int speed = 4;

public:
    
    HL_Square();
    ~HL_Square();

    std::vector<HL_Rectangle*> myRects;
    SDL_Rect* myRect;
    SDL_Color* myColour = new SDL_Color();
    
    void Init(int xpos = 100, int ypos = 100, int wid = 100, int hig = 100);
    void Render(SDL_Renderer* theRenderer);
    void Update();
    void Input(SDL_Event _event);
    
    void Move(int vert, int hori);
    bool CopyColour(const HL_Square &otherSquare);

    static int SquareCounterTotal;
    int SquareCounter;

    

};

