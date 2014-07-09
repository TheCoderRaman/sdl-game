//! \file SDLAudio.cpp
//!
//! \author  Owain Davies
//! \date    May 2014
//!
//! This holds the interface between SDL Audio and LEngine audio systems
//!	

#include "SDL_TTF.h"
#include <stdint.h>

#include "SDLTexture.h"

#include "SDLText.h"
#include "debug.h"

//====================================================
//   Text Interface
//====================================================
SDLInterface::SDLText::SDLText()
{
	if( -1 == TTF_Init() )
	{
		DEBUG_LOG( "Can't initialise text: %s", TTF_GetError() );
	}
	else
	{
		DEBUG_LOG( "Initialised text correctly" );
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

	if( toReturn.GetFont() == NULL )
	{
		DEBUG_LOG( "Can't load font: %s", TTF_GetError() );
	}

	return toReturn;
}

void SDLInterface::SDLText::CloseFont( SDLInterface::SDL_Font* font )
{
	TTF_CloseFont( font->GetFont() );
}

//====================================================
void SDLInterface::SDLText::RenderTextSolid( SDLInterface::Surface* surfaceToReturn, SDL_Font* font, const char* text )
{
	SDL_Color colour = { 255, 255, 0, 255 };

	surfaceToReturn->CreateFromSurface( TTF_RenderText_Solid( font->GetFont(), text, colour ) );
}
