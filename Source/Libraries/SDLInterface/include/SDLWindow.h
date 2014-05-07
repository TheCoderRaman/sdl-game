//! \file SDLWindow.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for Window.cpp
//!
#ifndef _SDL_WINDOW_H
#define _SDL_WINDOW_H

// Includes
#include "types.h"


#include "SDLHelper.h" // for friending

// Forward declares
struct SDL_Window;

// Start the SDLInterface Namespace
namespace SDLInterface
{

	//! \brief SDL_Window wrapper
	class Window
	{
		//! Friends with Helper to let it access it's internals
		friend class Helper;
	public:

		//! default ctor and dtor
		Window();
		~Window();

		//! \brief create the window
		eError Create( int w, int h );

		//! \brief destroy the window
		eError Destroy();

	private:

		//! \brief the internal SDL window
		SDL_Window* 		m_SDL_Window;


	};
}

#endif //_SDL_WINDOW_H