// On linux compile with:
// g++ -std=c++17 main.cpp -o prog -lSDL2 -ldl
// On windows compile with (if using mingw)
// g++ main.cpp -o prog.exe -lmingw32 -lSDL2main -lSDL2
// On Mac compile with:
// clang++ main.cpp -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2

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

    BackgroundAnimation water = BackgroundAnimation(&application);
    Enemies enemies = Enemies(&application);
    BattleShip ship = BattleShip();


    bool gameIsRunning = water.load(&application) &&
    	    enemies.load() &&
    	    ship.load(&application);

    while(gameIsRunning)
    {
    	Uint32 start = SDL_GetTicks();

        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            // Handle each specific event
            if(event.type == SDL_QUIT)
            {
                gameIsRunning= false;
            }
            if(event.type == SDL_MOUSEMOTION)
            {
				ship.move(event.motion.x, event.motion.y);
            }
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {


            	/*
                if(event.button.button == SDL_BUTTON_LEFT){
                    SDL_SetTextureBlendMode(texture2,SDL_BLENDMODE_ADD);
                }
                else if(event.button.button == SDL_BUTTON_MIDDLE){
                    SDL_SetTextureBlendMode(texture2,SDL_BLENDMODE_BLEND);
                }
                else if(event.button.button == SDL_BUTTON_RIGHT){
                    SDL_SetTextureBlendMode(texture2,SDL_BLENDMODE_MOD);
                }
            	*/
            }
            if(event.type == SDL_KEYUP)
            {
				if(event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q)
					gameIsRunning = false;
            }
        }
        
        application.prepareFrame();

        water.tick(start);

		water.display(&application);
		enemies.display();
		ship.display(&application);

        application.displayFrame();

        enemies.move(20, 20, application.getWidth() - 20, application.getHeight() - 20);

    }

    water.destroy();
    enemies.destroy();
    ship.destroy();
    
    return true;
}

int main(int argc, char* argv[])
{
    if (runApp())
    	SDL_Quit();

    return 0;
}
