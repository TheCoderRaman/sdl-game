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
#include "eError.h"

#include "SDLEventLoop.h"

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
			0,  	// Uses whichever default device is available
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

	// Sanity check to see if renderer has been created
	DEBUG_ASSERT(NULL != m_SDL_Renderer);

	EventLoop::RunOnMainThread_Sync( err,
	[ & ]()->eError
	{

		SDL_RenderClear( m_SDL_Renderer );

		SDL_SetRenderDrawColor( m_SDL_Renderer, 0, 120, 255, 255 );

		SDL_Rect myRect;

		myRect.h = 100;
		myRect.w = 100;
		myRect.x = 50;
		myRect.y = 50;

		SDL_RenderDrawRect( m_SDL_Renderer, &myRect );

		SDL_RenderPresent( m_SDL_Renderer );

		return eError::NoErr;
	} );


	return err;
}

//========================================================
eError SDLInterface::Renderer::Destroy()
{
	eError err = eError::NoErr;

	SDL_DestroyRenderer(m_SDL_Renderer);

	m_SDL_Renderer = nullptr;

	return err;
}
