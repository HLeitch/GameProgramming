// SDLBeginning.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SDL.h"







int Exercise1()
{

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return 1;
	}

	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);

	int width = DM.w;
	int height = DM.h;


	SDL_Window* window = SDL_CreateWindow("Harrison Roddie Leitch 16657607", width / 2, height / 2, 800, 600, SDL_WINDOW_SHOWN);

	SDL_Delay(4000);
	
	return 0;
}

int Exercise3Triangle()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return 1;
	}


	SDL_Window* window = SDL_CreateWindow("Harrison Roddie Leitch 16657607", 100,100, 800, 800,SDL_WINDOW_RESIZABLE);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//paint over with last colour
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 250, 250, 250, 250);

	//Drawing the lines we want. (A, B), (B, C), (C, A)
	SDL_RenderDrawLine(renderer, 0, 400, 400, 0);
	SDL_RenderDrawLine(renderer, 400, 400, 400, 0);
	SDL_RenderDrawLine(renderer, 0, 400, 400, 400);

	//Renders render
	SDL_RenderPresent(renderer);


	SDL_Delay(4000);

	return 0;

}
int Exercise3Rect()
{

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return 1;
	}


	SDL_Window* window = SDL_CreateWindow("Harrison Roddie Leitch 16657607", 100, 100, 800, 800, SDL_WINDOW_RESIZABLE);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//paint over with last colour
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 250, 250);

	SDL_Rect myRect;
	myRect.x = 360;
	myRect.y = 360;
	myRect.w = 80;
	myRect.h = 80;



	SDL_RenderDrawRect(renderer, &myRect);


	//Renders render
	SDL_RenderPresent(renderer);


	SDL_Delay(4000);

	return 0;



}
	int randColorElement()
{
	int r = rand() % 255 + 1;


	return r;




}

int Exercise3Lines()
{

		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return 1;
	}


	SDL_Window* window = SDL_CreateWindow("Harrison Roddie Leitch 16657607", 100,100, 1000, 1000,SDL_WINDOW_RESIZABLE);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(renderer, 0, 0, 250, 250);

	int count = 0;
	int limit = (rand() % 10045 + 1);
	while ( count < limit)
	{
		int xStart = rand() % 1000 + 1;
		int xEnd = rand() % 1000 + 1;
		int yEnd = rand() % 1000 + 1;
		int ystart = rand() % 1000 + 1;

		SDL_SetRenderDrawColor(renderer, randColorElement(), randColorElement(), randColorElement(),randColorElement());

		SDL_RenderDrawLine(renderer, xStart, ystart, xEnd, yEnd);

		count++;

	}


	//Renders render
	SDL_RenderPresent(renderer);


	SDL_Delay(4000);

	return 0;
}






int main(int argc, char* argv[])
{
	return Exercise3Lines();
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
