//! \file SDLMain.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Description
//! 
#include "SDLMain.h"

#include "SDL.h"
#include "SDL_image.h"

#include "debug.h"
#include "eError.h"

//========================================================
eError SDLInterface::Init()
{
	eError err = eError::NoErr;

	//Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        DEBUG_LOG( "SDL could not initialize! Error: %s", SDL_GetError() );
        err |= eError::SDL_Fatal;
    }

	//Initialise the SDL_image library
	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_PNG) < 0)
	{
		DEBUG_LOG("IMG could not initialize! Error: %s", IMG_GetError());
		err |= eError::SDL_Fatal;
	}

    return err;
}

//========================================================
eError SDLInterface::Quit()
{
	eError err = eError::NoErr;

    SDL_Quit();

	return err;
}