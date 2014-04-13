//! \file SDLRenderer.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Description
//! 
#include "SDLRenderer.h"

#include "SDL.h"

#include "debug.h"

SDLRenderer::SDLRenderer()
: m_SDL_Renderer(NULL)
{

}

SDLRenderer::~SDLRenderer()
{
	DEBUG_ASSERT(NULL == m_SDL_Renderer);
}

// Create
eError SDLRenderer::Create( SDLWindow* window )
{
	eError err = eError_noErr;

	// Create the renderer
	m_SDL_Renderer = SDL_CreateRenderer( SDLHelper::GetSDL_Window(window),
			-1,  	// Uses whichever default device is available
			0);		// Uses the default SDL_RENDERER_ACCELERATED

	if (NULL == m_SDL_Renderer)
	{
		DEBUG_LOG("Renderer failed to be created");
		err = eError_SDL_Fatal;
	}

	return err;
}

// Render
eError SDLRenderer::Render()
{
	eError err = eError_noErr;
	return err;
}

// Destroy
eError SDLRenderer::Destroy()
{
	eError err = eError_noErr;

	SDL_DestroyRenderer(m_SDL_Renderer);

	return err;
}
