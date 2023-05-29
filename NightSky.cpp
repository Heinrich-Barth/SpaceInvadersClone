/*
 * AnimationWater.cpp
 *
 *  Created on: May 26, 2023
 *      Author: oldforrest
 */
#include "NightSky.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cstdlib>

NightSky::NightSky(SDLApplication *application) : MoveableRandomObject(std::string("./images/stars.png"))
{
	this->screenWidth = application->getWidth();
	this->screenHeight = application->getHeight();
}

NightSky::~NightSky()
{
	this->destroy();
}

Uint32 NightSky::createRandomPace()
{
	return 100;
}

Uint32 NightSky::createRandomStartDelay()
{
	return 0;
}

int NightSky::createRandomDirY()
{
	return 1;
}

void NightSky::createRandomStartPosition(SDL_Rect *source, SDL_Rect *target)
{
	source->y = 0;
	source->x = 0;

	target->x = 0;
	target->y = 0;
}

bool NightSky::forceTextureToResultion()
{
	return true;
}

bool NightSky::move(int dir, SDL_Rect *source, SDL_Rect *target)
{
	if (source->y + source->h + dir < getTextureHeight())
	{
		source->y += dir;
		return true;
	}
	else
		return false;
}
