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
#include "SDLTexture.h"

//========================================================
SDLInterface::Renderer::Renderer()
: m_SDL_Renderer(nullptr)
, m_bRendering( false )
{

}

//========================================================
SDLInterface::Renderer::~Renderer()
{
	DEBUG_ASSERT(nullptr == m_SDL_Renderer);
}

//========================================================
eError SDLInterface::Renderer::Create(Window* window)
{
	eError err = eError::NoErr;

	EventLoop::RunOnMainThread_Sync(err,
	[&]()->eError
	{
		eError err = eError::NoErr;

		// Attempt to get the renderer from the window
		m_SDL_Renderer = SDL_GetRenderer(Helper::GetSDL_Window(window));

		// if the window did not give a renderer
		if (m_SDL_Renderer == nullptr)
		{
			// log this, it's not fatal
			DEBUG_LOG("SDL_Window did not have renderer, creating new one");

			// Create a new renderer
			m_SDL_Renderer = SDL_CreateRenderer(Helper::GetSDL_Window(window),
				-1,  	// Uses whichever default device is available
				0);		// Uses the default SDL_RENDERER_ACCELERATED
		}

		return err;
	});
	

	// Sanity check here
	if (m_SDL_Renderer == nullptr)
	{
		DEBUG_LOG("Renderer failed to be created: %s", SDL_GetError());
		err |= eError::SDL_Fatal;
	}

	return err;
}

//========================================================
eError SDLInterface::Renderer::RenderStart()
{
	eError err = eError::NoErr;

	// Sanity check
	DEBUG_ASSERT(!m_bRendering);

	// Sanity check to see if renderer has been created
	DEBUG_ASSERT(nullptr != m_SDL_Renderer);

	EventLoop::RunOnMainThread_Sync(err,
		[&]()->eError
	{
		// Start by clearing the render buffer
		SDL_RenderClear(m_SDL_Renderer);

		return eError::NoErr;
	});

	// Set us to be rendering
	m_bRendering = true;

	return err;
}

//========================================================
eError SDLInterface::Renderer::RenderRectangle(const Rect& src, int r, int g, int b, int a, bool fill  /* = true */)
{
	eError err = eError::NoErr;

	// Sanity check
	DEBUG_ASSERT(m_bRendering);

	// Sanity check to see if renderer has been created
	DEBUG_ASSERT(nullptr != m_SDL_Renderer);

	SDL_Rect myRect = RECT_TO_SDL_RECT(src);

	EventLoop::RunOnMainThread_Sync(err,
		[&]()->eError
	{

		// Set the draw colour
		SDL_SetRenderDrawColor(m_SDL_Renderer, r, g, b, a);


		// Draw the rectangle
		SDL_RenderDrawRect(m_SDL_Renderer, &myRect);

		// fill the rectangle
		if ( fill )
			SDL_RenderFillRect(m_SDL_Renderer, &myRect);


		// Reset the draw colour
		SDL_SetRenderDrawColor(m_SDL_Renderer, 255, 255, 255, 255);

		return eError::NoErr;
	});

	return err;
}

//========================================================
eError SDLInterface::Renderer::RenderTexture(Texture* tex, const Rect& src, const Rect& dest)
{
	eError err = eError::NoErr;

	// Sanity check
	DEBUG_ASSERT(m_bRendering);

	// Sanity check to see if renderer has been created
	DEBUG_ASSERT(nullptr != m_SDL_Renderer);

	// Create the two SDL_Rects
	SDL_Rect source			= RECT_TO_SDL_RECT(src);
	SDL_Rect destination	= RECT_TO_SDL_RECT(dest);

	EventLoop::RunOnMainThread_Sync(err,
		[&]()->eError
	{
		// Copy the texture over to the renderer
		SDL_RenderCopy(m_SDL_Renderer, Helper::GetSDL_Texture(tex), &source, &destination);

		return eError::NoErr;
	});

	return err;
}

//========================================================
eError SDLInterface::Renderer::RenderEnd()
{
	eError err = eError::NoErr;

	// Sanity check
	DEBUG_ASSERT(m_bRendering);

	// Sanity check to see if renderer has been created
	DEBUG_ASSERT(nullptr != m_SDL_Renderer);

	EventLoop::RunOnMainThread_Sync( err,
	[ & ]()->eError
	{
		//Present the rendered image
		SDL_RenderPresent( m_SDL_Renderer );

		return eError::NoErr;
	} );

	// Set us to not be rendering
	m_bRendering = false;

	return err;
}

//========================================================
eError SDLInterface::Renderer::Destroy()
{
	eError err = eError::NoErr;


	EventLoop::RunOnMainThread_Sync(err,
	[&]()->eError
	{
		eError err = eError::NoErr;

		SDL_DestroyRenderer(m_SDL_Renderer);

		return err;
	});

	m_SDL_Renderer = nullptr;

	return err;
}
