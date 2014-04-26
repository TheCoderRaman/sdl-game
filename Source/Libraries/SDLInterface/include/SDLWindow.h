//! \file SDLWindow.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for SDLWindow.cpp
//!
#ifndef _SDL_WINDOW_H
#define _SDL_WINDOW_H

// Includes
#include "types.h"

// for friending
#include "SDLHelper.h"

// Forward declares
struct SDL_Window;
struct SDL_Surface;

// Start the SDLInterface Namespace
namespace SDLInterface
{

	//! \brief SDL_Window wrapper
	class SDLWindow
	{
		//! Friends with SDLHelper to let it access it's internals
		friend class SDLHelper;
	public:

		//! default ctor and dtor
		SDLWindow();
		~SDLWindow();

		//! \brief create the window
		eError Create();

		//! \brief update the window
		eError Update();

		//! \brief destroy the window
		eError Destroy();

	private:

		//! \brief the internal SDL window
		SDL_Window* 		m_SDL_Window;

		//! \brief the internal SDL surface
		SDL_Surface* 		m_SDL_Surface;

	};
}

#endif //_SDL_WINDOW_H