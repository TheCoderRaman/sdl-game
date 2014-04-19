//! \file SDLMain.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Description
//! 
#include "SDLMain.h"

#include "SDL.h"
#include "debug.h"
#include "eError.h"

// Initialise SDL
eError SDLMain::Init()
{
	eError err = eError::noErr;

	//Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        DEBUG_LOG( "SDL could not initialize! SDL_Error: %s", SDL_GetError() );
        err |= eError::SDL_Fatal;
    }

    return err;
}

// Quit SDL
eError SDLMain::Quit()
{
	eError err = eError::noErr;

    SDL_Quit();

	return err;
}