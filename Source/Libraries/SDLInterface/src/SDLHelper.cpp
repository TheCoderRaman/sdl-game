//! \file SDLHelper.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Container for various SDL_ variable accessors or helpers
//!
#include "SDLHelper.h"

#include "SDLRenderer.h"
#include "SDLWindow.h"

//========================================================
SDL_Renderer*	SDLInterface::SDLHelper::GetSDL_Renderer(SDLRenderer* renderer)
{
	return renderer->m_SDL_Renderer;
}

//========================================================
SDL_Window*		SDLInterface::SDLHelper::GetSDL_Window(SDLWindow* window)
{
	return window->m_SDL_Window;
}

//========================================================
SDL_Surface*	SDLInterface::SDLHelper::GetSDL_Surface(SDLWindow* window)
{
	return window->m_SDL_Surface;
}
