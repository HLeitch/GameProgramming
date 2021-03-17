#include "HL_GameWorld.h"
#include <math.h>



void HL_GameWorld::Init()
{
	GameWindow* gameWindow = new GameWindow('n');

	renderer = gameWindow->myRenderer;

    
    timer = new HL_Timer();

}

void HL_GameWorld::Input()
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

void HL_GameWorld::Update()
{
    int xval = 300 * std::sin((6.2821 / 1000) * (frameCounter));

    float yval = 300*std::cos((6.2821/1000)*(frameCounter));

    SinusoidalPoint* p = new SinusoidalPoint(xval+600, (yval)+600);

    points.push_back(p);
    frameCounter+=111;
    

}

void HL_GameWorld::Render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 250);

    SDL_RenderClear(renderer);



    for (SinusoidalPoint* p : points)
    {
        p->Render(renderer);
    }

    SDL_RenderPresent(renderer);
}

void HL_GameWorld::Run()
{
    Init();

    while (!done)
    {
        //Allows for timing of frame
        timer->resetTicksTimer();

        Input();

        Update();

        Render();



        if (timer->getTicks() < delta_Time)
        {
            SDL_Delay(delta_Time - timer->getTicks());

        }



    }


}
