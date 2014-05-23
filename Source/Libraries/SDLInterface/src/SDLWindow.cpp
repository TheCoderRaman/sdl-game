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
#include "SDLError.h"

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
SDLInterface::Error SDLInterface::Window::Create(int w, int h)
{
	Error err = Error::NoErr;

    //Create window
	EventLoop::RunOnMainThread_Sync(err,
		[&]()->Error {

		m_SDL_Window = SDL_CreateWindow("Window",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			w,h,SDL_WINDOW_SHOWN);

		return Error::NoErr;
	});


    if( m_SDL_Window == NULL )
    {
        DEBUG_LOG( "Window could not be created! SDL_Error: %s", SDL_GetError() );
        err |= Error::Window_create_fail;
    }

	return err;
}

//========================================================
SDLInterface::Error SDLInterface::Window::Destroy()
{
	Error err = Error::NoErr;

    //Destroy window
	EventLoop::RunOnMainThread_Sync(err,
		[&]()->Error {

		SDL_DestroyWindow(m_SDL_Window);

		return Error::NoErr;
	});

    m_SDL_Window = nullptr;

	return err;
}