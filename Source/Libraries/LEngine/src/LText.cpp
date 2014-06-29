//! \file LText.cpp
//!
//! \author  Owain Davies
//! \date    June 2014
//!
//! 
//! 
//!

#include "LText.h"

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
	m_SDLTextLibrary.Destroy();
}

//====================================================
void LText::LoadFont( const char* filename, const char* name, int size )
{
	SDLInterface::SDL_Font font( m_SDLTextLibrary.OpenFont( filename, size ) );

	m_fonts.push_back( std::make_tuple( font, name, size ) );
}

//====================================================
SDLInterface::Surface* LText::DrawText( const char* name, int size, const char* text )
{
	SDLInterface::SDL_Font* fontToUse = FindFont( name, size );

	return m_SDLTextLibrary.RenderTextSolid( fontToUse, text );
}

//====================================================
SDLInterface::SDL_Font* LText::FindFont( const char* name, int size )
{
	SDLInterface::SDL_Font* toReturn = nullptr;

	for( auto font : m_fonts )
	{
		if( 0 == strcmp( name, std::get< 1 >( font ) ) && std::get< 2 >( font ) == size )
		{
			toReturn = &std::get< 0 >( font );
		}
	}

	return toReturn;
}
