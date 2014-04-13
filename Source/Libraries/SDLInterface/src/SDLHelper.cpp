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

//! \brief Gets the SDL_Renderer from an SDLRenderer
SDL_Renderer*	SDLHelper::GetSDL_Renderer(SDLRenderer* renderer)
{
	return renderer->m_SDL_Renderer;
}

//! \brief Gets the SDL_Window from an SDLWindow
SDL_Window*		SDLHelper::GetSDL_Window(SDLWindow* window)
{
	return window->m_SDL_Window;
}

//! \brief Gets the SDL_Surface from an SDLWindow
SDL_Surface*		SDLHelper::GetSDL_Surface(SDLWindow* window)
{
	return window->m_SDL_Surface;
}
