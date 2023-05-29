/*
 * Enemy.h
 *
 *  Created on: May 26, 2023
 *      Author: oldforrest
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include "SDLApplication.h"
#include "Displayable.h"
#include <string>
#include <array>

class Enemy : public Displayable
{
private:
	SDL_Texture *texture1;

	unsigned int enemyLine;

	int m_nMostLeftX;
	int m_nMostRightX;

public:
	Enemy(int nCount = 8);
	virtual ~Enemy();

	bool load(SDLApplication *application);
	void destroy();
	void display(SDLApplication *application, int nOffsetX, int nOffsetY);
	bool isEmpty();

	int getMostLeftX();
	int getMostRightX();
};

#endif /* ENEMY_H_ */
