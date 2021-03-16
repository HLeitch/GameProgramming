#include "HL_GameWorld.h"




void HL_GameWorld::Init()
{
	GameWindow* gameWindow = new GameWindow('n');

	renderer = gameWindow->myRenderer;

    theRow = new HL_SpaceInvaderRow();
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
            theRow->Input(SDLK_w);
        }


    }

   

}

void HL_GameWorld::Update()
{
    theRow->Update();


}

void HL_GameWorld::Render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 250);

    SDL_RenderClear(renderer);


    
    theRow->Render(renderer);

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
