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
#include "SDLError.h"

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
SDLInterface::Error SDLInterface::Renderer::Create(Window* window)
{
	Error err = Error::None;

	EventLoop::RunOnMainThread_Sync(err,
	[&]()->Error
	{
		Error err = Error::None;

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
		err |= Error::Renderer_create_fail;
	}

	return err;
}

//========================================================
SDLInterface::Error SDLInterface::Renderer::RenderStart()
{
	Error err = Error::None;

	// Sanity check
	DEBUG_ASSERT(!m_bRendering);

	// Sanity check to see if renderer has been created
	DEBUG_ASSERT(nullptr != m_SDL_Renderer);

	EventLoop::RunOnMainThread_Sync(err,
		[&]()->Error
	{
		// Start by clearing the render buffer
		SDL_RenderClear(m_SDL_Renderer);

		return Error::None;
	});

	// Set us to be rendering
	m_bRendering = true;

	return err;
}

//========================================================
SDLInterface::Error SDLInterface::Renderer::RenderRectangle(const Rect& src, int r, int g, int b, int a, bool fill  /* = true */)
{
	Error err = Error::None;

	// Sanity check
	DEBUG_ASSERT(m_bRendering);

	// Sanity check to see if renderer has been created
	DEBUG_ASSERT(nullptr != m_SDL_Renderer);

	SDL_Rect myRect = RECT_TO_SDL_RECT(src);
	
	
#ifndef WINDOWS_BUILD
	// On Linux and OSX we have to render this on the main thread
	// TODO: Work out how to ensure we don't need to do this
	// I _think_ it would be a case of binding the context
	EventLoop::RunOnMainThread_Sync(err,
		[&]()->Error
	{
#endif

		// Set the draw colour
		SDL_SetRenderDrawColor(m_SDL_Renderer, r, g, b, a);


		// Draw the rectangle
		SDL_RenderDrawRect(m_SDL_Renderer, &myRect);

		// fill the rectangle
		if ( fill )
			SDL_RenderFillRect(m_SDL_Renderer, &myRect);


		// Reset the draw colour
		SDL_SetRenderDrawColor(m_SDL_Renderer, 255, 255, 255, 255);

#ifndef WINDOWS_BUILD
		return Error::None;
	});
#endif

	return err;
}

//========================================================
SDLInterface::Error SDLInterface::Renderer::RenderTexture(Texture* tex, const Rect& src, const Rect& dest, float rotation /*= 0.0f*/, const Point& centerRot /*= Rect()*/, int flipValue /*= SDL_FLIP_NONE*/)
{
	Error err = Error::None;

	// Sanity check
//	DEBUG_ASSERT(m_bRendering);

	// Sanity check to see if renderer has been created
	DEBUG_ASSERT(nullptr != m_SDL_Renderer);

	// Create the two SDL_Rects
	SDL_Rect source			= RECT_TO_SDL_RECT(src);
	SDL_Rect destination	= RECT_TO_SDL_RECT(dest);
	SDL_Point rot			= { centerRot.x / 2, centerRot.y / 2 };
	SDL_RendererFlip  flip	= SDL_FLIP_NONE;

#ifndef WINDOWS_BUILD
	// On Linux and OSX we have to render this on the main thread
	// TODO: Work out how to ensure we don't need to do this
	// I _think_ it would be a case of binding the context
	EventLoop::RunOnMainThread_Sync(err,
		[&]()->Error
	{
#endif
		// Copy the texture over to the renderer
		SDL_RenderCopyEx(m_SDL_Renderer, 
						Helper::GetSDL_Texture(tex), 
						&source, 
						&destination,
						rotation,
						&rot,
						flip);

#ifndef WINDOWS_BUILD
		return Error::None;
	});
#endif

	return err;
}

//========================================================
SDLInterface::Error SDLInterface::Renderer::RenderEnd()
{
	Error err = Error::None;

	// Sanity check
	DEBUG_ASSERT(m_bRendering);

	// Sanity check to see if renderer has been created
	DEBUG_ASSERT(nullptr != m_SDL_Renderer);

	EventLoop::RunOnMainThread_Sync( err,
	[ & ]()->Error
	{
		//Present the rendered image
		SDL_RenderPresent( m_SDL_Renderer );

		return Error::None;
	} );

	// Set us to not be rendering
	m_bRendering = false;

	return err;
}

//========================================================
SDLInterface::Error SDLInterface::Renderer::Destroy()
{
	Error err = Error::None;


	EventLoop::RunOnMainThread_Sync(err,
	[&]()->Error
	{
		Error err = Error::None;

		SDL_DestroyRenderer(m_SDL_Renderer);

		return err;
	});

	m_SDL_Renderer = nullptr;

	return err;
}
