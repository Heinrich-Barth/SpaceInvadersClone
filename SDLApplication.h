/*
 * SDLApplication.h
 *
 *  Created on: May 26, 2023
 *      Author: oldforrest
 */

#ifndef SDLAPPLICATION_H_
#define SDLAPPLICATION_H_

#include <SDL2/SDL.h>

class SDLApplication {

private:

	SDL_Window *window;
	SDL_Renderer *renderer;

	int maxFrameRate;
	int width;
	int height;

public:
	SDLApplication();
	virtual ~SDLApplication();

	bool init();
	SDL_Renderer *getRenderer();

	void onResize();

	void prepareFrame();
	void displayFrame();

	int getWidth();
	int getHeight();
};

#endif /* SDLAPPLICATION_H_ */
