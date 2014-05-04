//! \file SDLWindow.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Description
//! 
#include "SDLWindow.h"

// extra includes
#include "SDL.h"

#include "debug.h"
#include "eError.h"

#include "SDLEventLoop.h"

//========================================================
SDLInterface::Window::Window()
: m_SDL_Window(nullptr)
{

}

//========================================================
SDLInterface::Window::~Window()
{
    // Sanity check here
	DEBUG_ASSERT( nullptr == m_SDL_Window );
}

//========================================================
eError SDLInterface::Window::Create()
{
	eError err = eError::NoErr;

    //Create window
    m_SDL_Window = SDL_CreateWindow( "Window", 
    	SDL_WINDOWPOS_UNDEFINED, 
    	SDL_WINDOWPOS_UNDEFINED, 
    	500, 
    	300, 
    	SDL_WINDOW_SHOWN );

    if( m_SDL_Window == NULL )
    {
        DEBUG_LOG( "Window could not be created! SDL_Error: %s", SDL_GetError() );
        err |= eError::SDL_Fatal;
    }
    else
    {
        //Get window surface
		m_Surface.CreateFromWindow(this);
    }

	return err;
}

//========================================================
eError SDLInterface::Window::UpdateSurface()
{
    eError err = eError::NoErr;

    // SDL Window functions must be run on the main thread
	EventLoop::RunOnMainThread_Sync(err,
	[&]()->eError {

		SDL_UpdateWindowSurface(m_SDL_Window);
		return eError::NoErr;
	});

    return err;
}

//========================================================
eError SDLInterface::Window::Destroy()
{
	eError err = eError::NoErr;

	//Deallocate surface
	m_Surface.Destroy();

    //Destroy window
    SDL_DestroyWindow( m_SDL_Window );
    m_SDL_Window = nullptr;

	return err;
}