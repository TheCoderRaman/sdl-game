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
#include "SDLSurface.h"
#include "SDLTexture.h"

//========================================================
SDL_Renderer*	SDLInterface::Helper::GetSDL_Renderer(Renderer* renderer)
{
	return renderer->m_SDL_Renderer;
}

//========================================================
SDL_Window*		SDLInterface::Helper::GetSDL_Window(Window* window)
{
	return window->m_SDL_Window;
}

//========================================================
SDL_Surface*	SDLInterface::Helper::GetSDL_Surface(Surface* surface)
{
	return surface->m_sdl_surface;
}

//========================================================
SDL_Texture*	SDLInterface::Helper::GetSDL_Texture(Texture* texture)
{
	return texture->m_sdl_texture;
}