#include "HL_GameWorld.h"




void HL_GameWorld::Init()
{
	GameWindow* gameWindow = new GameWindow('n');

	renderer = gameWindow->myRenderer;

    
        aGameContainerSquare.Init(50, 50, 0.0f, 5.0f, 5);

        aGameContainerSquare.ChangeColour(0, 0, 255, 255);
    
   
   

        

    timer = new HL_Timer();

}

void HL_GameWorld::Input()
{
    SDL_Event _event;
    while (SDL_PollEvent(&_event))
    {

        
    }
}

void HL_GameWorld::Update()
{
    aGameContainerSquare.Update();



}

void HL_GameWorld::Render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 250);

    SDL_RenderClear(renderer);



    aGameContainerSquare.Render(renderer);



    SDL_RenderPresent(renderer);
}

void HL_GameWorld::Run()
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "INTIALISATION STARTED");
    Init();
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "INTIALISATION FINISHED");

    
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
    Quit();

}

void HL_GameWorld::Quit()
{
    delete &aGameContainerSquare;
}
