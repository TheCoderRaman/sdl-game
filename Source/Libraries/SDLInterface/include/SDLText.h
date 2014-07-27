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
	//! \brief a Font class
	class SDL_Font
	{
	public:
		SDL_Font( TTF_Font* font );

		void		SetFont		( TTF_Font* font )		{ myFont = font;	}

		TTF_Font*	GetFont		( void )				{ return myFont;	}
		int			GetHeight	( void )				{ return iHeight;	}
		int			GetWidth	( const char* text );

	private:

		struct sdlFontCharAttributes
		{
			sdlFontCharAttributes( void )
				: thisChar( 'a' )
				, iAdvance( 0 )
				, iMaxX( 0 )
				, iMinX( 0 )
				, iMaxY( 0 )
				, iMinY( 0 )
			{}

			char thisChar;
			int iAdvance;			// width

			int iMaxX;
			int iMinX;
			int iMaxY;
			int iMinY;
		};

		int iHeight;
		int iTotalCurrentGlyphs;
		static const unsigned s_kiMaxGlyphs = 100;

		sdlFontCharAttributes charAttributes[ s_kiMaxGlyphs ];


		void	GetAllAttributes	( void );
		void	FillGlyphAttributes	( char character );

		sdlFontCharAttributes	GetAttributeForChar( char toGet );


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
