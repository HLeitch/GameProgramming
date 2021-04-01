// GameLoop Workshop 4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "HL_GameObject.h"
#include "SDL.h"
#include"GameWindow.h"
#include"HL_Timer.h"
//#include "HL_Rectangle.h"

#include "HL_GameWorld.h"
//#include "HL_Square.h"

//key press tracker
#define max_KEYS (256)
bool gKeys[MAX_KEYS];


// GLOBAL VARIABLES AND DECLARATIONS FOR BASIC GAME LOOP

SDL_Event _event;

HL_Square* theSquare;

bool done = false;


void Init()
{




}

void Input()
{
    while (SDL_PollEvent(&_event))
    {
        if (_event.type == SDL_QUIT)
            done = true;



        if (_event.type == SDL_KEYDOWN && _event.key.repeat == NULL)
        {
            switch (_event.key.keysym.sym) {
            case SDLK_ESCAPE:
                done = true;
                break;

            case SDLK_w:
                printf("W has been pressed \n");
                gKeys[SDLK_w] = true;
                break;
            }

        }
        if (_event.type == SDL_KEYUP && _event.key.repeat == NULL)
        {
            switch (_event.key.keysym.sym) {

            case SDLK_w:
                printf("W has been unpressed \n");
                gKeys[SDLK_w] = false;
                break;
            }

        }
        if (gKeys[SDLK_w])
        {
            printf("W is pressed!\n");
        }


    }

}
int Speed = 8;
void Update(GameWindow* gw, HL_Rectangle* gameObject)
{
    int* screenWidth = new int(200);
    int* screenHeight = new int(800);

    SDL_GetWindowSize(gw->myWindow, screenWidth, screenHeight);


}

void Render(SDL_Renderer* renderer, HL_Rectangle* gameObject)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 250);

    SDL_RenderClear(renderer);




    SDL_RenderPresent(renderer);
}

void GameLoop30fps()
{


    /*
    GameWindow* gameWindow = new GameWindow('n');

    HL_Timer* timer = new HL_Timer();

    HL_Rectangle* rect = new HL_Rectangle(80, 80, 50, 50);

    /// <summary>
    /// Time allowed per frame
    /// </summary>
    const int DELTA_TIME = 16;

    Init();
    Render(gameWindow->myRenderer, rect);

    while (!done)
    {
        //Allows for timing of frame
        timer->resetTicksTimer();

        Input();

        Update(gameWindow, rect);

        Render(gameWindow->myRenderer,rect);



        if (timer->getTicks() < DELTA_TIME)
        {
            SDL_Delay(DELTA_TIME - timer->getTicks());

        }



    }*/
}

HL_GameWorld myworld;

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 1;
    }

    // myworld.Init();
    myworld.Run();



    ////Experiments in workshop


    return 0;
}











// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
