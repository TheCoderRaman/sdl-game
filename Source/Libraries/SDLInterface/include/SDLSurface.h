//! \file SDLSurface.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for SDLSurface.cpp
//! References for how to use SDL_Surface can be found
//! here : https://wiki.libsdl.org/SDL_Surface
#ifndef _SDLSURFACE_H_
#define _SDLSURFACE_H_

#include "SDLCommon.h"

#include "SDLHelper.h" // for friending

// Forward declare the SDL_Surface type from SDL
struct SDL_Surface;

// Start the SDLInterface Namespace
namespace SDLInterface
{
	// Forward declare of window
	class Window;

	//! \brief wrapper class for SDL_Surface
	class Surface
	{
		//! Friends with Helper to let it access it's internals
		friend class Helper;
	public:

		//! \brief default constructor
		Surface();

		//! \brief default destructor
		~Surface();

		//! \brief Create the surface
		Error CreateFromBMP(const char* bmpFile);

		//! \brief Create the surface
		Error CreateFromFile(const char* file);

		//! \brief Create the surface from a window
		Error CreateFromWindow(Window* window);

		//! \brief Create the surface from another SDL surface
		Error CreateFromSurface( SDL_Surface* surface );

		//! \brief destroy the surface
		Error Destroy();

	private:

		//! \brief the internal SDL_Surface
		SDL_Surface* m_sdl_surface;

	};
}

#endif //_SDLSURFACE_H_