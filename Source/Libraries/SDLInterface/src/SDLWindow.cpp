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
eError SDLInterface::Window::Create(int w, int h)
{
	eError err = eError::NoErr;

    //Create window
	EventLoop::RunOnMainThread_Sync(err,
		[&]()->eError {

		m_SDL_Window = SDL_CreateWindow("Window",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			w,h,SDL_WINDOW_SHOWN);

		return eError::NoErr;
	});


    if( m_SDL_Window == NULL )
    {
        DEBUG_LOG( "Window could not be created! SDL_Error: %s", SDL_GetError() );
        err |= eError::SDL_Fatal;
    }

	return err;
}

//========================================================
eError SDLInterface::Window::Destroy()
{
	eError err = eError::NoErr;

    //Destroy window
	EventLoop::RunOnMainThread_Sync(err,
		[&]()->eError {

		SDL_DestroyWindow(m_SDL_Window);

		return eError::NoErr;
	});

    m_SDL_Window = nullptr;

	return err;
}