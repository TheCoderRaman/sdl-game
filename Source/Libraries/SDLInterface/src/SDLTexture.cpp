//! \file SDLTexture.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! References for how to use SDL_Texture can be found
//! here : https://wiki.libsdl.org/SDL_Texture
#include "SDLTexture.h"

#include "SDL.h"

#include "eError.h"
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

}

//========================================================
eError SDLInterface::Texture::Create()
{
	eError err = eError::NoErr;

	DEBUG_LOG("NOT IMPLEMENTED");

	return err;
}

//========================================================
eError SDLInterface::Texture::Create(Renderer* renderer, const char* file)
{
	eError err = eError::NoErr;

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

	// Create the texture
	m_sdl_texture = SDL_CreateTextureFromSurface(sdlRenderer, Helper::GetSDL_Surface(&tempSurf));

	// Error handling
	if (m_sdl_texture == NULL)
	{
		DEBUG_LOG("Texture could not be created from surface! SDL_Error: %s", SDL_GetError());
		err |= eError::SDL_Fatal;
	}

	tempSurf.Destroy();

	return err;
}

//========================================================
eError SDLInterface::Texture::Create(Renderer* renderer,Surface* surface)
{
	eError err = eError::NoErr;

	// Sanity checks
	DEBUG_ASSERT(renderer != nullptr);
	DEBUG_ASSERT(surface != nullptr);

	// Grab the surface and renderer
	SDL_Surface* sdlSurface = Helper::GetSDL_Surface(surface);
	SDL_Renderer* sdlRenderer = Helper::GetSDL_Renderer(renderer);

	// Sanity checks
	DEBUG_ASSERT(sdlSurface != nullptr);
	DEBUG_ASSERT(sdlRenderer != nullptr);

	// Create the texture
	m_sdl_texture = SDL_CreateTextureFromSurface(sdlRenderer, sdlSurface);

	// Error handling
	if (m_sdl_texture == NULL)
	{
		DEBUG_LOG("Texture could not be created from surface! SDL_Error: %s", SDL_GetError());
		err |= eError::SDL_Fatal;
	}

	return err;
}

//========================================================
eError SDLInterface::Texture::Destroy()
{
	eError err = eError::NoErr;

	// Sanity check
	DEBUG_ASSERT(m_sdl_texture != nullptr);

	// Destroy the texture
	SDL_DestroyTexture(m_sdl_texture);

	m_sdl_texture = nullptr;

	return err;
}