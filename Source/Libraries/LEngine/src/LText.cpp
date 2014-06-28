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
: butts( nullptr )
, m_surface( nullptr )
, bCreated( false )
{
	butts = new SDLInterface::Texture();
}

//====================================================
LText::~LText()
{
	// Delete all text
	delete butts;
	butts = nullptr;

	m_surface->Destroy();

	delete m_surface;
	m_surface = nullptr;
}

//====================================================
void LText::LoadFont( const char* filename, const char* name, int size )
{
	SDLInterface::SDL_Font font( m_SDLTextLibrary.OpenFont( filename, size ) );

	m_fonts.push_back( std::make_tuple( font, name, size ) );
}

//====================================================
void LText::DrawText( const char* name, int size, const char* text )
{
	SDLInterface::SDL_Font* fontToUse = FindFont( name, size );

	m_surface = m_SDLTextLibrary.RenderTextSolid( fontToUse, text );
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

//====================================================
LError LText::Render( LRenderer2D* renderer )
{
	if( m_surface != nullptr  && !bCreated )
	{
		butts->Create( &renderer->GetBaseRenderer(), m_surface );
		bCreated = true;
	}

	SDLInterface::Rect source = { 0, 0, 100, 100 };
	SDLInterface::Rect dest = { 0, 0, 100, 100 };

	if( bCreated )
	{
		renderer->GetBaseRenderer().RenderTexture( butts, source, dest );
	}

	return LError::NoErr;
}

