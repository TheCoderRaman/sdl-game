//! \file SDLSurface.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! References for how to use SDL_Surface can be found
//! here : https://wiki.libsdl.org/SDL_Surface
#include "SDLSurface.h"

// From Util
#include "eError.h"
#include "debug.h"

// SDLInterface includes
#include "SDLWindow.h"

#include "SDL.h"

//========================================================
SDLInterface::Surface::Surface()
: m_sdl_surface( nullptr )
{

}

//========================================================
SDLInterface::Surface::~Surface()
{

}

//========================================================
eError SDLInterface::Surface::CreateFromBMP(const char* bmpFile)
{
	eError err = eError::NoErr;

	// Sanity check
	DEBUG_ASSERT(m_sdl_surface == nullptr);

	// Get a surface from the BMP
	m_sdl_surface = SDL_LoadBMP(bmpFile);

	// Error handling
	if (m_sdl_surface == NULL)
	{
		DEBUG_LOG("Surface could not be created from %s! SDL_Error: %s", bmpFile,SDL_GetError());
		err |= eError::SDL_Fatal;
	}

	return err;
}

//========================================================
eError SDLInterface::Surface::CreateFromWindow(Window* window)
{
	eError err = eError::NoErr;

	// Sanity check
	DEBUG_ASSERT(m_sdl_surface == nullptr);

	// Get the SDL_Window from the Window
	SDL_Window* sdlwindow = Helper::GetSDL_Window(window);

	// Sanity check
	DEBUG_ASSERT(sdlwindow != nullptr);

	// Get the surface from the window
	m_sdl_surface = SDL_GetWindowSurface(sdlwindow);

	// Error handling
	if (m_sdl_surface == NULL)
	{
		DEBUG_LOG("Surface could not be fetched from window! SDL_Error: %s", SDL_GetError());
		err |= eError::SDL_Fatal;
	}

	return err;
}

//========================================================
eError SDLInterface::Surface::Destroy()
{
	eError err = eError::NoErr;

	// Sanity check
	DEBUG_ASSERT(m_sdl_surface != nullptr);

	// Free the SDL surface
	SDL_FreeSurface(m_sdl_surface);

	return err;
}