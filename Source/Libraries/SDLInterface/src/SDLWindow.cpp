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
SDLInterface::SDLWindow::SDLWindow()
: m_SDL_Window(nullptr)
, m_SDL_Surface(nullptr)
{

}

//========================================================
SDLInterface::SDLWindow::~SDLWindow()
{
    // Sanity check here
	DEBUG_ASSERT( nullptr == m_SDL_Window );
	DEBUG_ASSERT( nullptr == m_SDL_Surface);
}

//========================================================
eError SDLInterface::SDLWindow::Create()
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
        m_SDL_Surface = SDL_GetWindowSurface( m_SDL_Window );

        if( m_SDL_Surface == NULL )
        {
            DEBUG_LOG( "Surface could not be fetched! SDL_Error: %s", SDL_GetError() );
            err |= eError::SDL_Fatal;
        }
    }

	return err;
}

//========================================================
eError SDLInterface::SDLWindow::Update()
{
    eError err = eError::NoErr;

    // SDL Window functions must be run on the main thread
	SDLEventLoop::RunOnMainThread_Sync(err,
	[&]()->eError {

		SDL_UpdateWindowSurface(m_SDL_Window);
		return eError::NoErr;
	});

    return err;
}

//========================================================
eError SDLInterface::SDLWindow::Destroy()
{
	eError err = eError::NoErr;

	//Deallocate surface
    SDL_FreeSurface( m_SDL_Surface );
    m_SDL_Surface = nullptr;

    //Destroy window
    SDL_DestroyWindow( m_SDL_Window );
    m_SDL_Window = nullptr;

	return err;
}