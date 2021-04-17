#include "HL_GameWorld.h"
#include <math.h>



void HL_GameWorld::Init()
{
    

    GameWindow* gameWindow = new GameWindow('n');
    if (gameWindow != NULL)
    {
        SDL_Log("gameworld: created a new window");
    }
    renderer = gameWindow->myRenderer;
    SDL_Log("Render pointer in gameWorld : %p", &renderer);

    timerBar = new HL_GameObject;
    indicatorSquare = new HL_GameObject;
    rhythmObjects = new HL_RhythmObjectContainer;



    timerBar->Init(100, 5, timerWidth, 20);
    indicatorSquare->Init(300, 150, 400, 400);
    rhythmObjects->Init(150, 570, 5, 0, 8);


    timerBar->SetColour(255, 0, 0);
    indicatorSquare->SetColour(0, 0, 255);




    timer = new HL_Timer();

    RhythmReset();

}

void HL_GameWorld::Input()
{
    SDL_Event _event;
    while (SDL_PollEvent(&_event))
    {
        if (_event.type == SDL_QUIT)
        {
            Quit();

        }

        rhythmObjects->Input(_event);

    }
}
int x = 1;
float f = 0.00f;
std::string myString = "TESTER STRING";
void HL_GameWorld::Update()
{
    gameTimer += lastDeltaTime;

    
    //old c
   // SDL_Log("Testing x: %i float %f %s window pointer = %p ", x,f,myString.c_str(), &window);

    x++;
    f = f + 0.1;
    
    float percentTimeUsed= gameTimer;

    percentTimeUsed /= gameTime;

    float width = (1 - percentTimeUsed) * timerWidth;

    printf("width %f\n", width);
    timerBar->width = width;
    
    gameRoundTimer += lastDeltaTime;
    
    if (gameRoundTimer > maxGameRoundTime)
    {
        RhythmReset();
      indicatorSquare->SetColour(0,0,255);
    }
    if(rhythmObjects->activeObjects == rhythmObjects->PressedObjects())
    {
      
        indicatorSquare->SetColour(0, 255, 0);
  }
    if (rhythmObjects->activeObjects < rhythmObjects->PressedObjects())
    {
        indicatorSquare->SetColour(255, 0, 0);
    }

    aGameContainerSquare.Update();

    rhythmObjects->Update();

    

}

void HL_GameWorld::RhythmReset()
{
    for (HL_RhythmObject* ro : rhythmObjects->aListofRhythmObjects)
    {
        ro->active = false;
        ro->pressed = false;
        
    }
    rhythmObjects->roundCounter = 0;

    int activeRhythmObjects = (rand() % 8) + 1;
    rhythmObjects->activeObjects = activeRhythmObjects;
    int counter = 0;
    while (counter < activeRhythmObjects)
    {
        rhythmObjects->aListofRhythmObjects[counter]->active = true;
        counter++;
    }

    gameRoundTimer = 0;
}

void HL_GameWorld::Render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderClear(renderer);

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "GameObject rendered (%p)", this);

    aGameContainerSquare.Render(renderer);
    timerBar->Render(renderer);
    indicatorSquare->Render(renderer);
    rhythmObjects->Render(renderer);


    SDL_RenderPresent(renderer);
}

int HL_GameWorld::randColorElement()
{
    int r = rand() % 255 + 1;


    return r;




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

        lastDeltaTime = timer->getTicks();
        
    }
    Quit();
    
}

void HL_GameWorld::Quit()
{
    delete& aGameContainerSquare;


}
