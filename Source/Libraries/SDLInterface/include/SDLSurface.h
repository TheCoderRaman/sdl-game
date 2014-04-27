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

// Forward declare the SDL_Surface type from SDL
struct SDL_Surface;

// Start the SDLInterface Namespace
namespace SDLInterface
{
	//! \brief wrapper class for SDL_Surface
	class Surface
	{
	public:

		//! \brief default constructor
		Surface();

		//! \brief default destructor
		~Surface();

	private:

		//! \brief the internal SDL_Surface
		SDL_Surface* m_sdl_surface;

	};
}

#endif //_SDLSURFACE_H_