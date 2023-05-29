/*
 * Sprite.h
 *
 *  Created on: May 26, 2023
 *      Author: oldforrest
 */

#ifndef DISPLAYABLE_H_
#define DISPLAYABLE_H_

#include "SDLApplication.h"

class Displayable {
private:
	SDL_Rect dimensions;

	int width;
	int height;

protected:
	void setDimension(SDL_Texture *texture);

public:
	Displayable();
	virtual ~Displayable();

	virtual void display(SDLApplication *application);
	virtual bool load(SDLApplication *application);
	virtual void destroy();

	int getWidth();
	int getHeight();
};

#endif /* DISPLAYABLE_H_ */
