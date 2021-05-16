#pragma once
#include<iostream>
#include "SDL.h"

#define GAME_WINDOW_WIDTH  (1000)
#define GAME_WINDOW_HEIGHT  (1000)
class GameWindow
{
public:
	SDL_Window* myWindow;

	SDL_Renderer* myRenderer;
	
	GameWindow(const char& title);
	GameWindow(std::string title);

	GameWindow(const char& title, int w, int h);


	

private:
	int initWindow();

};

