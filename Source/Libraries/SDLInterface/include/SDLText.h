//! \file SDLAudio.h
//!
//! \author  Owain Davies
//! \date    May 2014
//!
//! Header for SDLAudio.cpp
//!	
#ifndef _SDLTTF_H_
#define _SDLTTF_H_

#include "SDLCommon.h"
#include "SDLSurface.h"

struct _TTF_Font;
typedef _TTF_Font TTF_Font;

struct SDL_Surface;

// Start the SDLInterface Namespace
namespace SDLInterface
{
	//=====================================
	//! \brief a Text class
	class SDL_Font
	{
	public:
		SDL_Font( TTF_Font* font ) : myFont ( nullptr ) { myFont = font; }

		void SetFont( TTF_Font* font ) { myFont = font; }
		TTF_Font* GetFont( void ) { return myFont; }
	private:
		TTF_Font* myFont;
	};

	//=====================================
	//! \brief a Text class
	class SDLText
	{
	public:

		SDLText( void );
		~SDLText( void );

		SDL_Font		OpenFont( const char* filename, int size );
		void			RenderTextSolid( SDLInterface::Surface* surfaceToReturn, SDL_Font* font, const char* text );
		void			CloseFont( SDL_Font* font );
	};
}

#endif //_SDLTTF_H_
