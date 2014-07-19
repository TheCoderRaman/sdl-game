//! \file LText.cpp
//!
//! \author  Owain Davies
//! \date    June 2014
//!
//! 
//! 
//!

#include "LText.h"
#include "debug.h"

//====================================================
LText::LText()
{
}

//====================================================
LText::~LText()
{
	for( auto font : m_fonts )
	{
		m_SDLTextLibrary.CloseFont( &std::get< 0 >( font ) );
	}
}

//====================================================
void LText::Destroy()
{
}

//====================================================
void LText::LoadFont( const char* filename, const char* name, int size )
{
	SDLInterface::SDL_Font font( m_SDLTextLibrary.OpenFont( filename, size ) );

	m_fonts.push_back( std::make_tuple( font, name, size ) );
}

//====================================================
void LText::DrawText( SDLInterface::Surface* toRenderTo, const char* name, int size, const char* text, SDLInterface::Rect* textureSize )
{
	SDLInterface::SDL_Font* fontToUse = FindFont( name, size );

	DEBUG_ASSERT( fontToUse );

	textureSize->h = fontToUse->GetHeight();
	textureSize->w = fontToUse->GetWidth( text );

	m_SDLTextLibrary.RenderTextSolid( toRenderTo, fontToUse, text );
}

//====================================================
SDLInterface::SDL_Font* LText::FindFont( const char* name, int size )
{
	SDLInterface::SDL_Font* toReturn = nullptr;

	for( auto font : m_fonts )
	{
		if( 0 == strcmp( name, std::get< 1 >( font ) ) )
		{
			if( std::get< 2 >( font ) == size )
			{
				toReturn = &( std::get< 0 >( font ) );
				break;
			}
		}
	}

	return toReturn;
}
