//! \file SDLTexture.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! References for how to use SDL_Texture can be found
//! here : https://wiki.libsdl.org/SDL_Texture
#include "SDLTexture.h"

#include "SDL.h"

#include "SDLError.h"
#include "debug.h"

#include "SDLSurface.h"
#include "SDLEventLoop.h"

//========================================================
SDLInterface::Texture::Texture()
: m_sdl_texture(nullptr)
{

}

//========================================================
SDLInterface::Texture::~Texture()
{
	DEBUG_ASSERT(m_sdl_texture == nullptr);
}

//========================================================
SDLInterface::Error SDLInterface::Texture::Create()
{
	Error err = Error::NoErr;

	DEBUG_LOG("NOT IMPLEMENTED");

	return err;
}

//========================================================
SDLInterface::Error SDLInterface::Texture::Create(Renderer* renderer, const char* file)
{
	Error err = Error::NoErr;

	// Sanity checks
	DEBUG_ASSERT(renderer != nullptr);
	DEBUG_ASSERT(file != nullptr);

	// Grab the surface and renderer
	Surface tempSurf;
	err |= tempSurf.CreateFromFile(file);

	// Grab the renderer
	SDL_Renderer* sdlRenderer = Helper::GetSDL_Renderer(renderer);

	// Sanity checks
	DEBUG_ASSERT(sdlRenderer != nullptr);

	EventLoop::RunOnMainThread_Sync(err,
	[&]()->Error
	{
		// Create the texture
		m_sdl_texture = SDL_CreateTextureFromSurface(sdlRenderer, Helper::GetSDL_Surface(&tempSurf));

		return Error::NoErr;
	});

	// Error handling
	if (m_sdl_texture == NULL)
	{
		DEBUG_LOG("Texture could not be created from surface! SDL_Error: %s", SDL_GetError());
		err |= Error::Texture_create_fail;
	}

	tempSurf.Destroy();

	return err;
}

//========================================================
SDLInterface::Error SDLInterface::Texture::Create(Renderer* renderer, Surface* surface)
{
	Error err = Error::NoErr;

	// Sanity checks
	DEBUG_ASSERT(renderer != nullptr);
	DEBUG_ASSERT(surface != nullptr);

	EventLoop::RunOnMainThread_Sync(err,
	[&]()->Error
	{
		// Grab the surface and renderer
		SDL_Surface* sdlSurface = Helper::GetSDL_Surface(surface);
		SDL_Renderer* sdlRenderer = Helper::GetSDL_Renderer(renderer);

		// Sanity checks
		DEBUG_ASSERT(sdlSurface != nullptr);
		DEBUG_ASSERT(sdlRenderer != nullptr);

		// Create the texture
		m_sdl_texture = SDL_CreateTextureFromSurface(sdlRenderer, sdlSurface);
		
		return Error::NoErr;
	});

	// Error handling
	if (m_sdl_texture == NULL)
	{
		DEBUG_LOG("Texture could not be created from surface! SDL_Error: %s", SDL_GetError());
		err |= Error::Texture_create_fail;
	}

	return err;
}

//========================================================
SDLInterface::Error SDLInterface::Texture::Destroy()
{
	Error err = Error::NoErr;

	// Sanity check
	DEBUG_ASSERT(m_sdl_texture != nullptr);

	EventLoop::RunOnMainThread_Sync(err,
	[&]()->Error
	{
		// Destroy the texture
		SDL_DestroyTexture(m_sdl_texture);

		return Error::NoErr;
	});

	m_sdl_texture = nullptr;

	return err;
}