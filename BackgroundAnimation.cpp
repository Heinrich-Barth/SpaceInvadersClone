/*
 * BackgroundAnimation.cpp
 *
 *  Created on: May 29, 2023
 *
 */
#include "BackgroundAnimation.h"

BackgroundAnimation::BackgroundAnimation(SDLApplication *application)
{
	list.push_back(std::make_unique<NightSky>(application));
	
	// moving objects deactivated for the moment
	
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
	// this is actually not necessary as the objects would be cleared
	// via their destructors automatically once the list is cleared.
	// Yet, explicit destruction is better than implicit.
	for (const std::unique_ptr<MoveableRandomObject> &elem : list)
		elem->destroy();

	list.clear();
}

void BackgroundAnimation::tick(Uint32 time)
{
	for (const std::unique_ptr<MoveableRandomObject> &elem : list)
		elem->move(time);
}
