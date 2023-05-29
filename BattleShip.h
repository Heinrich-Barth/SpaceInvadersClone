/*
 * BattleShip.h
 *
 *  Created on: May 29, 2023
 *      Author: oldforrest
 */

#ifndef BATTLESHIP_H_
#define BATTLESHIP_H_

#include "SDLApplication.h"

class BattleShip {

private:
	SDL_Texture* texture;

	int mouseAbsoluteX;
	int mouseAbsoluteY;

	int mouseRelX;
	int mouseRelY;

	int mouseXMax;
	int mouseXMin;

	int width;
	int height;

	SDL_Rect rectSource;
	SDL_Rect position;

	Uint32 timeLastMoved;

public:
	BattleShip();
	virtual ~BattleShip();

	bool load(SDLApplication *application);
	bool display(SDLApplication *application);
	void destroy();

	void move(int x, int y);
};

#endif /* BATTLESHIP_H_ */
