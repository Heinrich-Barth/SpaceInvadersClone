/*
 * MoveableRandomObject.h
 *
 *  Created on: May 29, 2023
 *      Author: oldforrest
 */

#ifndef MOVEABLERANDOMOBJECT_H_
#define MOVEABLERANDOMOBJECT_H_


#include <SDL2/SDL.h>

#include <string>
#include "SDLApplication.h"
#include "Displayable.h"

class MoveableRandomObject {

private:
	std::string file;
	SDL_Texture* texture;

	SDL_Rect sourceRect;
	SDL_Rect targetRect;

	Uint32 pace;
	Uint32 nextMove;

	int dirY;

	int textureWidth;
	int textureHeight;

	int screenWidth;
	int screenHeight;

private:
	void createRandomPosision();
	void selectTextureRect(SDL_Rect *rect, int textureWidth, int textureHeight, int screenWidth, int screenHeight);

protected:

	virtual Uint32 createRandomPace();
	virtual Uint32 createRandomStartDelay();
	virtual int createRandomDirY();
	virtual void createRandomStartPosition(SDL_Rect *source, SDL_Rect *target);
	virtual bool move(int dir, SDL_Rect *source, SDL_Rect *target);
	virtual bool forceTextureToResultion();

	int getScreenWidth();
	int getScreenHeight();

	int getTextureWidth();
	int getTextureHeight();

public:
	MoveableRandomObject(std::string file);
	virtual ~MoveableRandomObject();

	bool load(SDLApplication *application);
	void display(SDLApplication *application);
	void destroy();
	void move(Uint32 unCurrentTime);
};


#endif /* MOVEABLERANDOMOBJECT_H_ */
