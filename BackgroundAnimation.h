/*
 * BackgroundAnimation.h
 *
 *  Created on: May 29, 2023
 *      Author: oldforrest
 */

#ifndef BACKGROUNDANIMATION_H_
#define BACKGROUNDANIMATION_H_

#include "SDLApplication.h"
#include "MoveableRandomObject.h"
#include "NightSky.h"
#include <memory>
#include <vector>

class BackgroundAnimation {
private:
	std::vector<std::unique_ptr<MoveableRandomObject>> list;

public:
	BackgroundAnimation(SDLApplication *application);
	virtual ~BackgroundAnimation();

	void display(SDLApplication *application);
	bool load(SDLApplication *application);

	void tick(Uint32 time);
	void destroy();
};

#endif /* BACKGROUNDANIMATION_H_ */
