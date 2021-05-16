#include "GameWindow.h"

GameWindow::GameWindow(const char &title)
{
	if (initWindow() == 0);
	{
		SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO,"Initialised window\n");


	}

	myWindow =  SDL_CreateWindow(&title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

	myRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Window and Renderer Created: (%p) (%p)",&myWindow,&myRenderer);
}
GameWindow::GameWindow(std::string title)
{
	if (initWindow() == 0);
	{
		SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Initialised window\n");


	}
	
	myWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (GAME_WINDOW_WIDTH), (GAME_WINDOW_HEIGHT), SDL_WINDOW_RESIZABLE);

	myRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Window and Renderer Created: (%p) (%p)", &myWindow, &myRenderer);
}
GameWindow::GameWindow(const char& title, int w, int h)
{
	if (initWindow() != 0);
	{
		
		SDL_LogError(SDL_LOG_CATEGORY_ERROR,"Unable to initalise SDL:%p\n", SDL_GetError());

	}

	myWindow =  SDL_CreateWindow(&title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);

	myRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);

}

int GameWindow::initWindow()
{
if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return 1;
	}
else
{
	return 0;
}

}