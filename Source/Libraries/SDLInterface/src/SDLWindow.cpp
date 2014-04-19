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

// Default constructor
SDLWindow::SDLWindow()
: m_SDL_Window(nullptr)
, m_SDL_Surface(nullptr)
{

}

// Default destructor
SDLWindow::~SDLWindow()
{
    // Sanity check here
	DEBUG_ASSERT( nullptr == m_SDL_Window );
	DEBUG_ASSERT( nullptr == m_SDL_Surface);
}

// Create the window
eError SDLWindow::Create()
{
	eError err = eError::noErr;

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

// Update the window
eError SDLWindow::Update()
{
    eError err = eError::noErr;

    //Update the surface
    SDL_UpdateWindowSurface( m_SDL_Window );

    return err;
}

// Destroy the window
eError SDLWindow::Destroy()
{
	eError err = eError::noErr;

	//Deallocate surface
    SDL_FreeSurface( m_SDL_Surface );
    m_SDL_Surface = nullptr;

    //Destroy window
    SDL_DestroyWindow( m_SDL_Window );
    m_SDL_Window = nullptr;

	return err;
}