/*
 * Enemy.cpp
 *
 *  Created on: May 26, 2023
 *      Author: oldforrest
 */

#include "Enemy.h"

#include <bitset>

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <bitset>

inline SDL_Texture *safe_destory_texture(SDL_Texture *candidate)
{
	if (candidate != nullptr)
		SDL_DestroyTexture(candidate);

	return nullptr;
}

unsigned int createEnemyBits(int nCount)
{
	unsigned int bit1 = 1;
	unsigned int temp = 1 << 1;
	unsigned int bitRow = 0;

	while (temp != 0)
	{
		bit1 = bit1 << 1;
		temp = temp << 1;
	}

	for (int i = 0; i < nCount; i++)
	{
		bitRow = bitRow | bit1;
		bit1 = bit1 >> 1;
	}

	return bitRow;
}

Enemy::Enemy(int nCount)
{
	this->texture1 = nullptr;

	enemyLine = createEnemyBits(nCount);
	m_nMostLeftX = 0;
	m_nMostRightX = 0;

	std::cout << "Enemy created" << std::endl;
}

Enemy::~Enemy()
{
	this->destroy();
}

bool Enemy::load(SDLApplication *application)
{
	this->texture1 = IMG_LoadTexture(application->getRenderer(), "./images/monster1.png");
	this->setDimension(this->texture1);
	return this->texture1 != nullptr;
}

void Enemy::destroy()
{
	texture1 = safe_destory_texture(texture1);
}

const float g_fScaleFactor = 1.0f;

int Enemy::getMostLeftX()
{
	return m_nMostLeftX;
}

int Enemy::getMostRightX()
{
	return m_nMostRightX;
}

bool Enemy::isEmpty()
{
	return enemyLine == 0;
}

void Enemy::display(SDLApplication *application, int nOffsetX, int nOffsetY)
{
	if (enemyLine == 0)
		return;

	SDL_Renderer *renderer = application->getRenderer();
	SDL_Texture *texture = texture1;

	const float fScale = g_fScaleFactor;
	const int enemyHeight = getHeight() * fScale;
	const int enemyWidth = getWidth() * fScale;
	const int spaceBetweenX = enemyWidth / 2;
	const int enemyOccupyWidth = enemyWidth + spaceBetweenX;

	SDL_Rect rect;
	rect.x = nOffsetX;
	rect.y = nOffsetY;
	rect.w = enemyWidth;
	rect.h = enemyHeight;

	unsigned int pos = -1;
	int firstEnemyX = -1;
	int lastEnemyX = -1;


	do
	{
		if ( (enemyLine & pos) != 0)
		{
			lastEnemyX = rect.x;

			if (firstEnemyX == -1)
				firstEnemyX = rect.x;

			SDL_RenderCopy(renderer, texture, NULL, &rect);
		}

		pos = pos >> 1;
		rect.x += enemyOccupyWidth;
	}
	while (pos > 0);

	m_nMostLeftX = firstEnemyX;
	m_nMostRightX = lastEnemyX;
}
