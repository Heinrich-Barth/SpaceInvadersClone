/*
 * Missiles.h
 *
 *  Created on: May 30, 2023
 */

#ifndef MISSILE_H_
#define MISSILE_H_

#include "SDLApplication.h"

class Missile
{
private:
	SDL_Rect m_Position;
	int m_nDeltaY;
	int m_nBorderY;
	Uint32 timeOffset;
	Uint32 timeNextMove;

public:
	Missile(int x, int y, int maxY, bool isShipMissle);
	virtual ~Missile();

	void display(SDLApplication *application);
	bool move(Uint32 currentTime);
	bool isVisible();
	SDL_Rect *getPosition();
};

#endif /* MISSILE_H_ */
