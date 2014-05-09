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
#include "SDLEventLoop.h"

#include "SDL.h"
#include "SDL_image.h"

//========================================================
SDLInterface::Surface::Surface()
: m_sdl_surface( nullptr )
{

}

//========================================================
SDLInterface::Surface::~Surface()
{
	DEBUG_ASSERT(m_sdl_surface == nullptr);
}

//========================================================
eError SDLInterface::Surface::CreateFromBMP(const char* bmpFile)
{
	eError err = eError::NoErr;

	// Sanity check
	DEBUG_ASSERT(m_sdl_surface == nullptr);

	EventLoop::RunOnMainThread_Sync(err,
	[&]()->eError
	{
		// Get a surface from the BMP
		m_sdl_surface = SDL_LoadBMP(bmpFile);

		return eError::NoErr;
	});

	// Error handling
	if (m_sdl_surface == NULL)
	{
		DEBUG_LOG("Surface could not be created from %s! SDL_Error: %s", bmpFile,SDL_GetError());
		err |= eError::SDL_Fatal;
	}

	return err;
}

//========================================================
eError SDLInterface::Surface::CreateFromFile(const char* file)
{
	eError err = eError::NoErr;

	// Sanity check
	DEBUG_ASSERT(m_sdl_surface == nullptr);

	EventLoop::RunOnMainThread_Sync(err,
	[&]()->eError
	{
		// Get a surface from the BMP
		m_sdl_surface = IMG_Load(file);

		return eError::NoErr;
	});

	// Error handling
	if (m_sdl_surface == NULL)
	{
		DEBUG_LOG("Surface could not be created from %s! SDL_Error: %s", file, SDL_GetError());
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

	EventLoop::RunOnMainThread_Sync(err,
	[&]()->eError
	{
		// Get the surface from the window
		m_sdl_surface = SDL_GetWindowSurface(sdlwindow);

		return eError::NoErr;
	});

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

	EventLoop::RunOnMainThread_Sync(err,
	[&]()->eError
	{
		// Free the SDL surface
		SDL_FreeSurface(m_sdl_surface);

		return eError::NoErr;
	});

	m_sdl_surface = nullptr;

	return err;
}