//! \file SDLAudio.cpp
//!
//! \author  Owain Davies
//! \date    May 2014
//!
//! This holds the interface between SDL Audio and LEngine audio systems
//!	

#include "SDL_ttf.h"
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
	SDL_Color colour = { 0, 0, 0, 255 };

	surfaceToReturn->CreateFromSurface( TTF_RenderText_Solid( font->GetFont(), text, colour ) );
}


//====================================================
//					      Font
//====================================================
SDLInterface::SDL_Font::SDL_Font( TTF_Font* font )
: myFont( nullptr )
, iHeight( 0 )
, iTotalCurrentGlyphs( 0 )

{
	myFont = font;

	DEBUG_ASSERT( myFont );

	// If we have a valid font, fill this class with attributes
	GetAllAttributes();
}

//====================================================
int SDLInterface::SDL_Font::GetWidth( const char* text )
{
	int iWidth = -1;

	unsigned iStringLength = SDL_strlen( text );

	// Iterate through every char
	for( unsigned uLoop = 0; uLoop < iStringLength; ++uLoop )
	{
		iWidth += GetAttributeForChar( text[ uLoop ] ).iAdvance;
	}
	
	return iWidth;
}

//====================================================
void SDLInterface::SDL_Font::GetAllAttributes( void )
{
	iHeight = TTF_FontHeight( myFont );

	char glyph = 'a';

	for( unsigned uLoop = 0; uLoop < s_kiMaxGlyphs; ++uLoop )
	{
		FillGlyphAttributes( glyph );
		++glyph; // move along the alphabet
	}
}

//====================================================
SDLInterface::SDL_Font::sdlFontCharAttributes SDLInterface::SDL_Font::GetAttributeForChar( char toGet )
{
	char glyph = 'a';

	int iDifference = toGet - glyph; // work out which char we have

	if( iDifference < 0 )
	{
		iDifference = 0;
	}

	DEBUG_ASSERT( charAttributes[ iDifference ].thisChar == toGet );

	return charAttributes[ iDifference ];
}

//====================================================
void SDLInterface::SDL_Font::FillGlyphAttributes( char character )
{
	TTF_GlyphMetrics( myFont,
					  character,
					  &charAttributes[ iTotalCurrentGlyphs ].iMinX,
					  &charAttributes[ iTotalCurrentGlyphs ].iMaxX,
					  &charAttributes[ iTotalCurrentGlyphs ].iMinY,
					  &charAttributes[ iTotalCurrentGlyphs ].iMaxY,
					  &charAttributes[ iTotalCurrentGlyphs ].iAdvance );

	charAttributes[ iTotalCurrentGlyphs ].thisChar = character;

	++iTotalCurrentGlyphs;
}
