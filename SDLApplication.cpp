/*
 * SDLApplication.cpp
 *
 *  Created on: May 26, 2023
 *      Author: oldforrest
 */

#include "SDLApplication.h"
#include <iostream>
#include <SDL_image.h>

SDLApplication::SDLApplication()
{
	window = nullptr;
	renderer = nullptr;
	maxFrameRate = 60;
	width = 0;
	height = 0;
}

SDLApplication::~SDLApplication() {

	if (renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
		std::cout << "SDL renderer destroyed" << std::endl;
	}

	if (window != nullptr)
	{
		SDL_DestroyWindow(window);
		std::cout << "SDL window destroyed" << std::endl;
	}
}

bool SDLApplication::init()
{
	// Initialize the video subsystem.
	if (window != nullptr)
		return true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not be initialized: " << SDL_GetError();
		return false;
	}

	SDL_CaptureMouse(SDL_TRUE);

	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		std::cout << "SDL image could not be initialized: " << IMG_GetError() ;
		return false;
	}

	window = SDL_CreateWindow("C++ SDL2 Window",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640,480, 0);
	if (window == nullptr)
		return false;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
		return false;

	onResize();
	return true;
}

SDL_Renderer *SDLApplication::getRenderer()
{
	return renderer;
}

int SDLApplication::getWidth()
{
	return width;
}

int SDLApplication::getHeight()
{
	return height;
}

void SDLApplication::onResize()
{
	SDL_GetWindowSize(window, &width, &height);
}

void SDLApplication::prepareFrame()
{
    SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}

void SDLApplication::displayFrame()
{
	SDL_RenderPresent(renderer);
}
