#include "HL_GameWorld.h"




void HL_GameWorld::Init()
{
	GameWindow* gameWindow = new GameWindow(char("Conways Game Of Life"),gWorldSize*3,gWorldSize*3);


	renderer = gameWindow->myRenderer;

    
        //aGameContainerSquare.Init(50, 50, 0.0f, 5.0f, 5);

       //aGameContainerSquare.ChangeColour(0, 0, 255, 255);
    
    renderingRectangle.x = 0; renderingRectangle.y = 0;
    renderingRectangle.w = 3; renderingRectangle.h = 3;

    for (int i = 0; i < gWorldSize; i++)
    {
        for (int j = 0; j < gWorldSize; j++)
        {
            int aliveDecider = std::rand();
            if (aliveDecider % 100 < chanceOfAliveAtStart)
            {
                gWorld[i][j] = true;
            }
        }
    }

   
        
            gWorld[10][0] = true;
            gWorld[10][1] = true;
            gWorld[12][0] = true;

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
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Neighbours of [9,0] = (%i) ", countNeighbour(9, 0));
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Neighbours of [10,0] = (%i) ", countNeighbour(10, 0));
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Neighbours of [11,1] = (%i) ", countNeighbour(11, 1));

    
    for (int i = 0; i < gWorldSize; i++)
    {
        for (int j = 0; j < gWorldSize; j++)
        {
            int neighbours = countNeighbour(i, j);
            gNewWorld[i][j] = gWorld[i][j];
            if (neighbours < 2)
            {
                gNewWorld[i][j] = false;
            }
            else if ((neighbours == 2 || neighbours == 3)&&(gWorld[i][j]))
            {
                continue;
            }
            else if (neighbours > 3)
            {
                gNewWorld[i][j] = false;

            }

            else if ((neighbours == 3) && (!gWorld[i][j]))
            {
                gNewWorld[i][j] = true;
            }


        }
    }
    for (int i = 0; i < gWorldSize; i++)
    {
        for (int j = 0; j < gWorldSize; j++)
        {
            gWorld[i][j] = gNewWorld[i][j];
        }
    }

}

void HL_GameWorld::WorldRendering()
{
    for (int i = 0; i < gWorldSize; i++)
    {
        for (int j = 0; j < gWorldSize; j++)
        {
            renderingRectangle.x = (i * renderingRectangle.w);
            renderingRectangle.y = (j * renderingRectangle.h);
            RenderPoint(i, j);
        }
    }

}

void HL_GameWorld::RenderPoint(int i, int j)
{
    if (gWorld[i][j] == false)
    {
        ///Keeping the background black saves a spectactular amount of frame time///

        //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        //SDL_RenderFillRect(renderer, &renderingRectangle);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &renderingRectangle);
    }



}

void HL_GameWorld::Render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 250);

    SDL_RenderClear(renderer);
    WorldRendering();


    



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

        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Frame Time = %i", timer->getTicks());

    }
    Quit();

}

void HL_GameWorld::Quit()
{
    delete &aGameContainerSquare;
}


int HL_GameWorld::countNeighbour(int cellx, int celly)
{
    int neighbours = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if ((i == 0) && (j == 0))
            {
                continue;
            }
            else
            {
                try {


                    if (gWorld[cellx + i][celly + j]) 
                    { neighbours++; }
                }
                catch(_exception)
                {
                    continue;
                }
            }

        }

    }
    return neighbours;

}