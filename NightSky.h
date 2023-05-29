/*
 * AnimationWater.h
 *
 *  Created on: May 26, 2023
 *      Author: oldforrest
 */

#ifndef NIGHTSKY_H_
#define NIGHTSKY_H_

#include <SDL2/SDL.h>

#include <string>
#include "SDLApplication.h"
#include "Displayable.h"
#include "MoveableRandomObject.h"

class NightSky : public MoveableRandomObject {
private:

	int screenWidth;
	int screenHeight;

protected:
	Uint32 createRandomPace() override;
	Uint32 createRandomStartDelay() override;
	int createRandomDirY() override;
	void createRandomStartPosition(SDL_Rect *source, SDL_Rect *target) override;
	bool move(int dir, SDL_Rect *source, SDL_Rect *target) override;
	bool forceTextureToResultion() override;
public:
	NightSky(SDLApplication *application);
	virtual ~NightSky();

};

#endif /* NIGHTSKY_H_ */
