//! \file SDLRect.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for SDLRect.cpp
//! References for how to use SDL_Rect can be found
//! here : https://wiki.libsdl.org/SDL_Rect

#ifndef _SDLRECT_H_
#define _SDLRECT_H_

// Includes
#include "types.h"

// for friending
#include "SDLHelper.h"

// for the rectangles
#include "SDLRect.h"

// Forward declare SDL struct 
struct SDL_Renderer;

#define RECT_TO_SDL_RECT(src) { src.x, src.y, src.w, src.h }

// Start the SDLInterface Namespace
namespace SDLInterface
{
	//! \brief the Rect class
	//! functions as a replacement for SDL_Rect, wrapping one would be unneeded and would complicate the interface somewhat
	struct Rect
	{
		// Member variables to immitate SDL_Rect
		int x; //! Upper left x coord
		int y; //! Upper left y coord
		int w; //! Width of the rectangle
		int h; //! Height of the rectangle
	};
}

#endif //_SDLRECT_H_