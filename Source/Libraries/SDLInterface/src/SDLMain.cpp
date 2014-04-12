#include "SDLMain.h"

#include "SDL.h"

// Initialise SDL
eError SDLMain::Init()
{
	eError err = eError_noErr;

	//Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        DEBUG_LOG( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        err = eError_SDL_Error;
    }

    return err;
}

// Quit SDL
eError SDLMain::Quit()
{
	eError err = eError_noErr;

    SDL_Quit();

	return err;
}