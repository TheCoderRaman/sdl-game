//! \file Renderer.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Description
//! 
#include "SDLRenderer.h"

#include "SDL.h"

#include "debug.h"
#include "eError.h"

//========================================================
SDLInterface::Renderer::Renderer()
: m_SDL_Renderer(NULL)
{

}

//========================================================
SDLInterface::Renderer::~Renderer()
{
	DEBUG_ASSERT(NULL == m_SDL_Renderer);
}

//========================================================
eError SDLInterface::Renderer::Create(Window* window)
{
	eError err = eError::NoErr;

	// Create the renderer
	m_SDL_Renderer = SDL_CreateRenderer( Helper::GetSDL_Window(window),
			-1,  	// Uses whichever default device is available
			0);		// Uses the default SDL_RENDERER_ACCELERATED

	if (NULL == m_SDL_Renderer)
	{
		DEBUG_LOG("Renderer failed to be created");
		err |= eError::SDL_Fatal;
	}

	return err;
}

//========================================================
eError SDLInterface::Renderer::Render()
{
	eError err = eError::NoErr;
	return err;
}

//========================================================
eError SDLInterface::Renderer::Destroy()
{
	eError err = eError::NoErr;

	SDL_DestroyRenderer(m_SDL_Renderer);

	return err;
}
