#include "GameWindow.h"

GameWindow::GameWindow(const char &title)
{
	if (initWindow() == 0);
	{
		std::printf("Initialised window\n");


	}

	myWindow =  SDL_CreateWindow(&title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_SHOWN);

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