#pragma once
#include<iostream>
#include "SDL.h"
class GameWindow
{
public:
	SDL_Window* myWindow;

	SDL_Renderer* myRenderer;
	
	GameWindow(const char& title);


	

private:
	int initWindow();

};
