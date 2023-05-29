/*
 * MoveableRandomObject.cpp
 *
 *  Created on: May 29, 2023
 *      Author: oldforrest
 */

#include "MoveableRandomObject.h"
#include <SDL2/SDL_image.h>
#include <iostream>

MoveableRandomObject::MoveableRandomObject(std::string file)
{
	this->file = file;
	texture = nullptr;
	targetRect = {0,0,0,0};
	sourceRect = {0,0,0,0};
	pace = 0;
	nextMove = 0;
	dirY = 0;
	textureWidth = 0;
	textureHeight = 0;
	screenWidth = 0;
	screenHeight = 0;
}

MoveableRandomObject::~MoveableRandomObject()
{
	this->destroy();
}

int MoveableRandomObject::getScreenWidth()
{
	return screenWidth;
}

int MoveableRandomObject::getScreenHeight()
{
	return screenHeight;
}

int MoveableRandomObject::getTextureWidth()
{
	return textureWidth;
}

int MoveableRandomObject::getTextureHeight()
{
	return textureHeight;
}


void MoveableRandomObject::destroy()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

bool MoveableRandomObject::load(SDLApplication *application)
{
	screenWidth = application->getWidth();
	screenHeight = application->getHeight();

	this->texture = IMG_LoadTexture(application->getRenderer(), this->file.c_str());
	if (this->texture == nullptr)
		return false;

	//SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
	SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

	if (forceTextureToResultion())
	{
		this->selectTextureRect(&sourceRect, textureWidth, textureHeight, screenWidth, screenHeight);
		this->selectTextureRect(&targetRect, textureWidth, textureHeight, screenWidth, screenHeight);
	}
	else
	{
		this->selectTextureRect(&sourceRect, textureWidth, textureHeight, textureWidth, textureHeight);
		this->selectTextureRect(&targetRect, textureWidth, textureHeight, textureWidth, textureHeight);
	}

	this->createRandomPosision();
	this->nextMove += this->createRandomStartDelay();

	return true;
}

bool MoveableRandomObject::forceTextureToResultion()
{
	return false;
}

void MoveableRandomObject::selectTextureRect(SDL_Rect *rect, int textureWidth, int textureHeight, int screenWidth, int screenHeight)
{
	rect->x = 0;
	rect->y = 0;
	rect->w = textureWidth < screenWidth ? textureWidth : screenWidth;
	rect->h = textureHeight < screenHeight ? textureHeight : screenHeight;
}

Uint32 MoveableRandomObject::createRandomStartDelay()
{
	return rand() % 3000;
}

Uint32 MoveableRandomObject::createRandomPace()
{
	return rand() % 50;
}

int MoveableRandomObject::createRandomDirY()
{
	return 1;
}

void MoveableRandomObject::createRandomStartPosition(SDL_Rect *source, SDL_Rect *target)
{
	target->x = rand() %  (screenWidth - textureWidth);
	target->y = screenHeight;
}

void MoveableRandomObject::createRandomPosision()
{
	this->createRandomStartPosition(&this->sourceRect, &this->targetRect);

	this->dirY = createRandomDirY();
	this->pace = createRandomPace();
	this->nextMove = SDL_GetTicks() + pace;
}

void MoveableRandomObject::display(SDLApplication *application)
{
	SDL_RenderCopy(application->getRenderer(), texture, &sourceRect, &targetRect);
}

bool MoveableRandomObject::move(int dir, SDL_Rect *source, SDL_Rect *target)
{
	if (target->y + target->h <= 0)
		return false;

	target->y -= dir;
	return true;
}

void MoveableRandomObject::move(Uint32 unCurrentTime)
{
	if (unCurrentTime < nextMove)
		return;

	if (move(dirY, &sourceRect, &targetRect))
		nextMove = unCurrentTime + pace;
	else
		this->createRandomPosision();
}
