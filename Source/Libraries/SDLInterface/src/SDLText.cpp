//! \file SDLAudio.cpp
//!
//! \author  Owain Davies
//! \date    May 2014
//!
//! This holds the interface between SDL Audio and LEngine audio systems
//!	

#include "SDL_TTF.h"
#include <stdint.h>

#include "SDLText.h"
#include "debug.h"

//====================================================
//   Audio Interface
//====================================================
SDLInterface::SDLText::SDLText()
{
	if( -1 == TTF_Init() )
	{
		DEBUG_LOG( "Opening audio channel errors: %s", TTF_GetError() );
	}
}

//====================================================
SDLInterface::SDLText::~SDLText()
{
	TTF_Quit();
}

//====================================================
SDLInterface::SDL_Font SDLInterface::SDLText::OpenFont( const char* filename, int size )
{
	SDLInterface::SDL_Font toReturn = SDL_Font( TTF_OpenFont( filename, size ) );

	return toReturn;
}
