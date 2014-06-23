//! \file LText.h
//!
//! \author  Owain Davies
//! \date    June 2014
//!
//! Header for LText.cpp
//!
#ifndef _LTEXT_H_
#define _LTEXT_H_

#include "SDLText.h"
#include <vector>
#include <tuple>

class LText
{
public:
	LText( void );
	~LText( void );
	
	void LoadFont( const char* filename, const char* name, int size );
	void DrawText( const char* name, int size, const char* text );

private:

	const int iMAX_FONTS= 1;

	std::vector< std::tuple< SDLInterface::SDL_Font, const char*, int > > m_fonts;

	SDLInterface::SDL_Font* FindFont( const char* name, int size );
	
	SDLInterface::SDLText m_SDLTextLibrary;

};


#endif //_LTEXT_H_