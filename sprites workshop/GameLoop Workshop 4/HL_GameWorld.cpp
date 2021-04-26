#include "HL_GameWorld.h"
#include <math.h>

HL_GameWorld::HL_GameWorld()
{
}

void HL_GameWorld::Init()
{
    

    GameWindow* gameWindow = new GameWindow('n');
    if (gameWindow != NULL)
    {
        SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "gameworld: created a new window");
    }
    renderer = gameWindow->myRenderer;
    SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Render pointer in gameWorld : %p", &renderer);

    if (IMG_Init(SDL_INIT_EVERYTHING) == 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_Image Library failed to intitialise");
    }

    timerBar = new HL_GameObject;
    indicatorSquare = new HL_GameObject;
    rhythmObjects = new HL_RhythmObjectContainer;

    timerBar->Init(100, 5, timerWidth, 20);
    indicatorSquare->Init(300, 150, 400, 400);
    rhythmObjects->Init(150, 570, 5, 0, 8);


    timerBar->SetColour(255, 0, 0);
    indicatorSquare->SetColour(0, 0, 255);

    SDL_Rect myRect = { 0,0,100,100 };

   
    testSprite.load(renderer, "Content/spritesheet.png");

    timer = &gTimer;

    RhythmReset();

}

void HL_GameWorld::Input()
{
    SDL_Event _event;
    while (SDL_PollEvent(&_event))
    {
        if (_event.type == SDL_QUIT)
        {
            done = true;

        }
        if (_event.type == SDL_KEYDOWN) {
            if (!gKeys[_event.key.keysym.sym]) {
                SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "Key Pressed: %s Key number = %i", SDL_GetScancodeName(_event.key.keysym.scancode), _event.key.keysym.sym);
                gKeys[_event.key.keysym.sym] = true;


            }
            else {
                SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "Key Held: %s Key number = %i", SDL_GetScancodeName(_event.key.keysym.scancode), _event.key.keysym.sym);

            }
        }
        if (gKeys[SDLK_w])
        {
             Sprite_Frame++;
        }
        if (gKeys[SDLK_s])
        {
             Sprite_Frame--;
        }


		if (_event.type == SDL_KEYUP) {
            SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "Key Released : %s Key number = %i", SDL_GetScancodeName(_event.key.keysym.scancode), _event.key.keysym.sym);
gKeys[_event.key.keysym.sym] = false;
        }

        rhythmObjects->Input(_event);

        //WINDOW EVENTS
        if (_event.type == SDL_WINDOWEVENT)
        {
            if (_event.window.event == SDL_WINDOWEVENT_MOVED)
            {
                SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Window moved to (%i,%i)", _event.window.data1, _event.window.data2);
            }
            if (_event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Window resized to (%i X %i)", _event.window.data1, _event.window.data2);
            }
            if (_event.window.event == SDL_WINDOWEVENT_MINIMIZED)
            {
                SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Window Minimised");
            }
            if (_event.window.event == SDL_WINDOWEVENT_MAXIMIZED)
            {
                SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Window Maximised");
            }
        }
    }
}

void HL_GameWorld::Update()
{
    gameTimer += lastDeltaTime;


    //old c



    float percentTimeUsed = gameTimer;

    percentTimeUsed /= gameTime;

    float width = (1 - percentTimeUsed) * timerWidth;


    timerBar->width = width;

    gameRoundTimer += lastDeltaTime;

    if (gameRoundTimer > maxGameRoundTime)
    {
        RhythmReset();
        indicatorSquare->SetColour(0, 0, 255);
    }
    if (rhythmObjects->activeObjects == rhythmObjects->PressedObjects())
    {

        indicatorSquare->SetColour(0, 255, 0);
    }
    if (rhythmObjects->activeObjects < rhythmObjects->PressedObjects())
    {
        indicatorSquare->SetColour(255, 0, 0);
    }

    aGameContainerSquare.Update();

    rhythmObjects->Update();

    testSprite.update(gTimer.deltaTime);
    
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

   

    aGameContainerSquare.Render(renderer);
    timerBar->Render(renderer);
    indicatorSquare->Render(renderer);
    rhythmObjects->Render(renderer);

    testSprite.render(renderer);

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
        timer->deltaTime = timer->getTicks();
        
        SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "last frame time: %i (FPS = %i) ", timer->getTicks(),(1000/lastDeltaTime));

        
    }

    SDL_LogError(SDL_LOG_PRIORITY_ERROR, "GameLoop Sequence Broken");
    Quit();
    
}

void HL_GameWorld::Quit()
{
    IMG_Quit();
   
   //delete& aGameContainerSquare;
     SDL_Quit();

}
