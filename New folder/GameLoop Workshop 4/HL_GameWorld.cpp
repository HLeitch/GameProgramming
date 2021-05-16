#include "HL_GameWorld.h"
#include <math.h>
//Global music and sound files


Mix_Chunk* SOUND_aShot = NULL; //sound effects just use .wav for saftey
Mix_Music* SOUND_BackgroundMusic = NULL;

int CountDownTime = 1000;




void* HandleOneSecondTimerInterval(void)
{
    CountDownTime -= 1;
    if (CountDownTime < 0) CountDownTime = 0;
    return NULL;
}

Uint32 HeartBeatTimer(Uint32 interval, void* param)
{

    SDL_Log("HeartBeat Event pushed");
    Mix_PlayChannel(-1, SOUND_aShot, 0);
    CountDownTime -= 1;
    if (CountDownTime < 0) CountDownTime = 0;

    SDL_Event userEvent;
    userEvent.type = SDL_USEREVENT;
    userEvent.user.code = 0;

    ///SDL_PushEvent(&userEvent);
    SDL_Log("Heartbeat Timer = %i", CountDownTime);


    return CountDownTime;

}


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

  
    theTextureManager->SetRenderer(renderer);
    theTextureManager->LoadAllTexturesFromDirectory("Content/",true);

   //creating player//
    player = new HL_Player();
    _testBullet = new HL_Bullet();
    _GameEventsObjectContainer.aListofGameObjects.push_back(player);
    _GameEventsObjectContainer.aListofGameObjects.push_back(_testBullet);


    HL_Enemy* testEnemy = new HL_Enemy();
    _GameEventsObjectContainer.aListofGameObjects.push_back(testEnemy);

    _playersBulletContainer = new HL_BulletContainer();
    player->myBulletContainer = _playersBulletContainer;
    

    ///Walls
    HL_Wall* _upWall = new HL_Wall(0, -90, 1000, 100);
    _upWall->_objectName = "UP_WALL";
    _GameEventsObjectContainer.aListofGameObjects.push_back(_upWall);

    HL_Wall* _downWall = new HL_Wall(0, GAME_WINDOW_HEIGHT-10, GAME_WINDOW_WIDTH, 100);
    _GameEventsObjectContainer.aListofGameObjects.push_back(_downWall);
    _downWall->_objectName = "DOWN_WALL";

    HL_Wall* _rightWall = new HL_Wall(GAME_WINDOW_WIDTH-10, 0, 100, GAME_WINDOW_HEIGHT);
    _GameEventsObjectContainer.aListofGameObjects.push_back(_rightWall);
    _rightWall->_objectName = "RIGHT_WALL";

    HL_Wall* _leftWall = new HL_Wall(-90, 0, 100, GAME_WINDOW_HEIGHT);
    _GameEventsObjectContainer.aListofGameObjects.push_back(_leftWall);
    _leftWall->_objectName = "LEFT_WALL";
    /// <summary>
    /// Assign all collidable objects to ColliderObjects container
    /// </summary>
    for (HL_GameObject* gob : _GameEventsObjectContainer.aListofGameObjects)
    {
        if (gob->myCollider != nullptr)
        {
            _ColliderObjects.aListofGameObjects.push_back(gob);
        }
    }
    for (HL_GameObject* gob : _playersBulletContainer->bullets)
    {
        if (gob->myCollider != nullptr)
        {
            _ColliderObjects.aListofGameObjects.push_back(gob);
        }
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
   
    SDL_AddTimer(1000, &HeartBeatTimer, NULL);
    

    timer = &gTimer;

    RhythmReset();

    if (Mix_OpenAudio(222050, MIX_DEFAULT_FORMAT, 8, 4096) == -1)
    {
        SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Failed to load audio!");

    }
    else {
        // . needed for directory location
        SOUND_aShot = Mix_LoadWAV("./content/HeartBeat/heartbeat.wav");
        SOUND_BackgroundMusic = Mix_LoadMUS("./content/shortMusic.mp3");

        //Mix_PlayMusic(SOUND_BackgroundMusic, -1);
    }
}

void HL_GameWorld::Input()
{
    SDL_Event event;
    SDL_Event* _event = &event;
    while (SDL_PollEvent(_event))
    {        



        //Key state assignment
        if (_event->type == SDL_KEYDOWN) {
            if (!gKeys[_event->key.keysym.sym]) {
                SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "Key Pressed: %s Key number = %i", SDL_GetScancodeName(_event->key.keysym.scancode), _event->key.keysym.sym);
                gKeys[_event->key.keysym.sym] = true;

            }
            else {
                SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "Key Held: %s Key number = %i", SDL_GetScancodeName(_event->key.keysym.scancode), _event->key.keysym.sym);

            }
        }
		if (_event->type == SDL_KEYUP) {
            SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "Key Released : %s Key number = %i", SDL_GetScancodeName(_event->key.keysym.scancode), _event->key.keysym.sym);
            gKeys[_event->key.keysym.sym] = false;


        }


        if (_event->type == SDL_QUIT)
        {
            done = true;

        }

        if (gKeys[SDLK_w])
        {
             Sprite_Frame++;
        }
        if (gKeys[SDLK_s])
        {
             Sprite_Frame--;
        }
        if (gKeys[SDLK_m])
        {
            

            if (Mix_PausedMusic() != 0)
            {
                Mix_ResumeMusic(); //(SOUND_BackgroundMusic, -1);
            }
            else
            {
                Mix_PauseMusic();
            }
        }
       
        if (_event->type == SDL_USEREVENT)
        {
           if (_event->user.code == PLAYER_DAMAGED_EVENT)
            {
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Player Damaged Event Picked up in GameWorld Input Loop!! %p", &_event);

            }
           if (_event->user.code == ENEMY_DIED_EVENT)
           {
               SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Enemy died Event Picked up in GameWorld Input Loop!! %p", &_event);
           }
        }

        

        //WINDOW EVENTS
        if (_event->type == SDL_WINDOWEVENT)
        {
            if (_event->window.event == SDL_WINDOWEVENT_MOVED)
            {
                SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Window moved to (%i,%i)", _event->window.data1, _event->window.data2);
            }
            if (_event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Window resized to (%i X %i)", _event->window.data1, _event->window.data2);
            }
            if (_event->window.event == SDL_WINDOWEVENT_MINIMIZED)
            {
                SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Window Minimised");
            }
            if (_event->window.event == SDL_WINDOWEVENT_MAXIMIZED)
            {
                SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Window Maximised");
            }
        }
        
        /// <summary>
        /// GameObject InputHandling
        /// 
        /// </summary>
        _GameEventsObjectContainer.Input(_event);

        rhythmObjects->Input(_event);      



      
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
    
    _GameEventsObjectContainer.Update();

    _playersBulletContainer->Update();

    int colCounter = 0;

    for (HL_GameObject* gob : _ColliderObjects.aListofGameObjects)
    {
        gob->myCollider->Move();
    }

    for (HL_GameObject* gob : _ColliderObjects.aListofGameObjects)
    {
        int loopCounter = colCounter +1;

        //cycle through colliders and test if there is a collision
        while (loopCounter < _ColliderObjects.aListofGameObjects.size())
        {
            

            //Do not collide with objects of the same type
            if (gob->_objectType != _ColliderObjects.aListofGameObjects[loopCounter]->_objectType)
            {
                if ((gob->myCollider->findCollision(_ColliderObjects.aListofGameObjects[loopCounter]->myCollider)))
                {
                    gob->HasCollided(_ColliderObjects.aListofGameObjects[loopCounter]->myCollider);
                    _ColliderObjects.aListofGameObjects[loopCounter]->HasCollided(gob->myCollider);
                }
            }
            loopCounter++;
        }
        colCounter++;
    }

    

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
    SDL_SetRenderDrawColor(renderer, 255,255,255, 255);

    SDL_RenderClear(renderer);

   

    aGameContainerSquare.Render(renderer);
    timerBar->Render(renderer);
    indicatorSquare->Render(renderer);
    rhythmObjects->Render(renderer);
    
    _playersBulletContainer->Render(renderer);

    _GameEventsObjectContainer.Render(renderer);

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
        
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "last frame time: %i (FPS = %i) ", timer->getTicks(),(1000/lastDeltaTime));

        
    }

    SDL_LogError(SDL_LOG_PRIORITY_ERROR, "GameLoop Sequence Broken");
    Quit();
    
}

void HL_GameWorld::Quit()
{
    Mix_FreeChunk(SOUND_aShot);
    SOUND_aShot = NULL;
    Mix_FreeMusic(SOUND_BackgroundMusic);
    SOUND_BackgroundMusic = NULL;
   
    //delete &_GameEventsObjectContainer;
delete TextureManager::GetInstance();
    IMG_Quit();
   
   //delete& aGameContainerSquare;
     SDL_Quit();
 
}
