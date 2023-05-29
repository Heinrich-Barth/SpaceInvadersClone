#include <iostream>

#include <SDL2/SDL.h>

#include "SDLApplication.h"
#include "BackgroundAnimation.h"
#include "Enemies.h"
#include "Enemy.h"
#include "NightSky.h"
#include "BattleShip.h"

bool runApp()
{
    SDLApplication application{};

    if (!application.init())
    	return false;

    BackgroundAnimation background = BackgroundAnimation(&application);
    Enemies enemies = Enemies(&application);
    BattleShip ship = BattleShip();


    bool gameIsRunning = background.load(&application) &&
    	    enemies.load() &&
    	    ship.load(&application);

    while(gameIsRunning)
    {
    	Uint32 start = SDL_GetTicks();

        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                gameIsRunning= false;
            if(event.type == SDL_MOUSEMOTION)
		ship.move(event.motion.x, event.motion.y);

/*
	    if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(event.button.button == SDL_BUTTON_LEFT)
                    SDL_SetTextureBlendMode(texture2,SDL_BLENDMODE_ADD);
                else if(event.button.button == SDL_BUTTON_MIDDLE)
                    SDL_SetTextureBlendMode(texture2,SDL_BLENDMODE_BLEND);
                else if(event.button.button == SDL_BUTTON_RIGHT)
                    SDL_SetTextureBlendMode(texture2,SDL_BLENDMODE_MOD);
            }
*/
            if(event.type == SDL_KEYUP)
            {
		if(event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q)
			gameIsRunning = false;
            }
        }
        
        application.prepareFrame();

        background.tick(start);

	water.display(&application);
	enemies.display();
	ship.display(&application);

        application.displayFrame();

        enemies.move(20, 20, application.getWidth() - 20, application.getHeight() - 20);
    }

    background.destroy();
    enemies.destroy();
    ship.destroy();
    
    // the application window needs to be destroyed last
    // wrapped in its own scope, destroying all objects
    // could be done automatically via destructor calls
    return true;
}

void main(int argc, char* argv[])
{
    if (runApp())
    	SDL_Quit();
}
