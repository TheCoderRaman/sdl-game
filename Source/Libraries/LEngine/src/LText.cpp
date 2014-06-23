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
	// Delete all text
	
}

//====================================================
void LText::LoadFont( const char* filename, const char* name, int size )
{
	SDLInterface::SDL_Font font = m_SDLTextLibrary.OpenFont( filename, size );

	m_fonts.push_back( std::make_tuple( font, name, size ) );
}

//====================================================
void LText::DrawText( const char* name, int size, const char* text )
{
	// will need positioning etc
}

//====================================================
SDLInterface::SDL_Font* LText::FindFont( const char* name, int size )
{
	SDLInterface::SDL_Font* toReturn = nullptr;

	return toReturn;
}