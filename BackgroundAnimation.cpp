/*
 * BackgroundAnimation.cpp
 *
 *  Created on: May 29, 2023
 *      Author: oldforrest
 */

#include "BackgroundAnimation.h"

BackgroundAnimation::BackgroundAnimation(SDLApplication *application)
{
	list.push_back(std::make_unique<NightSky>(application));
	//list.push_back(std::make_unique<MoveableRandomObject>(std::string("./images/moon.png")));
	//list.push_back(std::make_unique<MoveableRandomObject>(std::string("./images/mars.png")));
}

BackgroundAnimation::~BackgroundAnimation()
{
}

void BackgroundAnimation::display(SDLApplication *application)
{
	for (const std::unique_ptr<MoveableRandomObject> &elem : list)
		elem->display(application);
}

bool BackgroundAnimation::load(SDLApplication *application)
{
	for (const std::unique_ptr<MoveableRandomObject> &elem : list)
	{
		if (!elem->load(application))
			return false;
	}

	return true;
}

void BackgroundAnimation::destroy()
{
	for (const std::unique_ptr<MoveableRandomObject> &elem : list)
		elem->destroy();

	list.clear();
}

void BackgroundAnimation::tick(Uint32 time)
{
	for (const std::unique_ptr<MoveableRandomObject> &elem : list)
		elem->move(time);
}
