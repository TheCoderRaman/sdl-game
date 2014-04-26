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

//========================================================
eError SDLMain::Init()
{
	eError err = eError::NoErr;

	//Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        DEBUG_LOG( "SDL could not initialize! SDL_Error: %s", SDL_GetError() );
        err |= eError::SDL_Fatal;
    }

    return err;
}

//========================================================
eError SDLMain::Quit()
{
	eError err = eError::NoErr;

    SDL_Quit();

	return err;
}