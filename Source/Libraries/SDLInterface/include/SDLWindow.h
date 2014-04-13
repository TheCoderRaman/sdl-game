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
#include "error.h"

// Forward declares
struct SDL_Window;
struct SDL_Surface;

class SDLWindow
{
public:

	SDLWindow();
	~SDLWindow();

	eError Create();

	eError Update();

	eError Destroy();

private:

	SDL_Window* 		m_SDL_Window;
	SDL_Surface* 		m_SDL_Surface;

};

#endif //_SDL_WINDOW_H