//! \file SDLWindow.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Description
//! 
#include "SDLRenderer.h"

SDLRenderer::SDLRenderer()
: myRenderer ( NULL )
{

}

SDLRenderer::~SDLRenderer()
{

}

// Create
eError SDLRenderer::Create( SDLWindow* window )
{
	eError err = eError_noErr;

	myRenderer = SDL_CreateRenderer( window, 
			-1,  	// Uses whichever default device is available
			0);		// Uses the default SDL_RENDERER_ACCELERATED

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

	SDL_DestroyRenderer(myRenderer);

	return err;
}
