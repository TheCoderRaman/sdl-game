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
: mySurface( nullptr )
{
	if( -1 == TTF_Init() )
	{
		DEBUG_LOG( "Can't initialise text: %s", TTF_GetError() );
	}
	else
	{
		DEBUG_LOG( "Initialised text correctly" );
	}

	mySurface = new Surface();
}

//====================================================
SDLInterface::SDLText::~SDLText()
{
	mySurface->Destroy();

	delete mySurface;
	mySurface = nullptr;

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

//====================================================
SDLInterface::Surface* SDLInterface::SDLText::RenderTextSolid( SDL_Font* font, const char* text )
{
	SDL_Color colour = { 255, 255, 0, 255 };

	mySurface->CreateFromSurface( TTF_RenderText_Solid( font->GetFont(), text, colour ) );

	return mySurface;
}
