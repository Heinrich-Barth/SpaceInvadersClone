/*
 * BattleShip.cpp
 *
 *  Created on: May 29, 2023
 *      Author: oldforrest
 */

#include "BattleShip.h"
#include <SDL2/SDL_image.h>

BattleShip::BattleShip() {
	texture = nullptr;
	width = 0;
	height = 0;
	rectSource = {0,0,0,0};
	position = {0,0,0,0};
	mouseAbsoluteX = -1;
	mouseAbsoluteY = -1;
	mouseRelX = 0;
	mouseRelY = 0;
	mouseXMax = 0;
	mouseXMin = 0;
	timeLastMoved = 0;
}

BattleShip::~BattleShip()
{
	this->destroy();
}

bool BattleShip::load(SDLApplication *application)
{
	this->texture = IMG_LoadTexture(application->getRenderer(), "./images/player.png");
	if (this->texture == nullptr)
		return false;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	position.x = application->getWidth() / 2 + width / 2;
	position.y = application->getHeight() - 20;
	position.w = width;
	position.h = height;

	mouseXMax = application->getWidth() - width - 20;
	timeLastMoved = SDL_GetTicks();
	return true;
}

bool BattleShip::display(SDLApplication *application)
{
	SDL_RenderCopy(application->getRenderer(), texture, NULL, &position);
	return true;
}

void BattleShip::move(int x, int y)
{
	if (mouseAbsoluteX == -1)
		mouseAbsoluteX = x;
	if (mouseAbsoluteY == -1)
		mouseAbsoluteY = y;

	int offsetX = position.x;
	int relX = x - mouseAbsoluteX;

	mouseAbsoluteX = x;
	mouseAbsoluteY = y;

	Uint32 timeNow = SDL_GetTicks();
	if (timeNow - timeLastMoved < 20)
		return;

	timeLastMoved = timeNow;

	if (relX < 0)
	{
		offsetX -= 15;
		if (offsetX < 0)
			offsetX = 0;
	}
	else if (relX > 0)
	{
		offsetX += 15;
		if (offsetX > mouseXMax)
			offsetX = mouseXMax;
	}

	position.x = offsetX;
}

void BattleShip::destroy()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}


SDL_Rect BattleShip::getPosition()
{
	return position;
}
