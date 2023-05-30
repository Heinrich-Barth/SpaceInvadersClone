#include <iostream>

#include <SDL2/SDL.h>
#include <vector>

#include "SDLApplication.h"
#include "BackgroundAnimation.h"
#include "Enemies.h"
#include "Enemy.h"
#include "NightSky.h"
#include "BattleShip.h"
#include "Missile.h"

void removeInvisibleMissiles(std::vector<std::unique_ptr<Missile>> *list)
{
	for(std::vector<std::unique_ptr<Missile>>::iterator iter = list->begin(); iter != list->end(); ++iter )
	{
		std::unique_ptr<Missile> &elem = *iter;
	    if (!elem->isVisible())
	    {
			iter = list->erase( iter );
			iter--;
	    }
	}
}

bool runApp()
{
	SDLApplication application = SDLApplication();

	if (!application.init())
		return false;

	BackgroundAnimation background = BackgroundAnimation(&application);
	Enemies enemies = Enemies(&application);
	BattleShip ship = BattleShip();

	constexpr size_t maxMissilesShip = 5;
	constexpr size_t maxMissilesEnemies = 5;

	std::vector<std::unique_ptr<Missile>> shipMissiles = {};

	bool gameIsRunning = background.load(&application)
			&& enemies.load()
			&& ship.load(&application);

	bool removeMissiles;
	SDL_Event event;
	while (gameIsRunning)
	{
		Uint32 start = SDL_GetTicks();

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameIsRunning = false;

			if (event.type == SDL_MOUSEBUTTONUP&& event.button.button == SDL_BUTTON_LEFT && shipMissiles.size() < maxMissilesShip)
			{
				SDL_Rect shipPosition = ship.getPosition();
				shipMissiles.push_back(std::make_unique<Missile>(shipPosition.x, shipPosition.y, 0, true));
				std::cout << "missile launched" << std::endl;
			}

			if (event.type == SDL_MOUSEMOTION)
			{
				int x, y;
				SDL_GetMouseState( &x, &y );
				ship.move(x, y);
			}

			if (event.type == SDL_KEYUP)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE
						|| event.key.keysym.sym == SDLK_q)
					gameIsRunning = false;
			}
		}

		application.prepareFrame();

		background.tick(start);

		background.display(&application);
		enemies.display();
		ship.display(&application);

		for (std::unique_ptr<Missile> &missile : shipMissiles)
			missile->display(&application);

		application.displayFrame();

		enemies.move(20, 20, application.getWidth() - 20,
				application.getHeight() - 20);

		removeMissiles = false;

		for (std::unique_ptr<Missile> &missile : shipMissiles)
		{
			if (!missile->move(start))
				removeMissiles = true;
		}

		if (removeMissiles)
		{
			std::cout << "remove needed" << std::endl;
			removeInvisibleMissiles(&shipMissiles);
		}
	}

	background.destroy();
	enemies.destroy();
	ship.destroy();

	// the application window needs to be destroyed last
	// wrapped in its own scope, destroying all objects
	// could be done automatically via destructor calls
	return true;
}

int main(int argc, char *argv[])
{
	if (runApp())
		SDL_Quit();

	return 0;
}
