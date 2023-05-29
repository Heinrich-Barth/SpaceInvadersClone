/*
 * Sprite.cpp
 *
 *  Created on: May 26, 2023
 *      Author: oldforrest
 */

#include "Displayable.h"

#include <iostream>

Displayable::Displayable()
{
	width = 0;
	height = 0;
}

Displayable::~Displayable()
{
}

void Displayable::setDimension(SDL_Texture *texture)
{
	if (texture == nullptr)
		return;

	int w = 0;
	int h = 0;

	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	if (w > 0 && h > 0)
	{
		this->width = w;
		this->height = h;
	}
}

int Displayable::getWidth()
{
	return width;
}

int Displayable::getHeight()
{
	return height;
}

void Displayable::display(SDLApplication *application)
{
}


bool Displayable::load(SDLApplication *application)
{
	return true;
}

void Displayable::destroy()
{
}
