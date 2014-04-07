#include "SDLWindow.h"

// extra includes
#include "SDL.h"

// Default constructor
SDLWindow::SDLWindow()
: m_SDL_Window ( NULL )
, m_SDL_Surface ( NULL )
{

}

// Default destructor
SDLWindow::~SDLWindow()
{
    // Sanity check here
	if ( m_SDL_Window || m_SDL_Surface )
        DEBUG_LOG("SDLWindow::~SDLWindow() called before Destroy");
}

// Create the window
eError SDLWindow::Create()
{
	eError err = eError_noErr;

    //Create window
    m_SDL_Window = SDL_CreateWindow( "Window", 
    	SDL_WINDOWPOS_UNDEFINED, 
    	SDL_WINDOWPOS_UNDEFINED, 
    	500, 
    	300, 
    	SDL_WINDOW_SHOWN );

    if( m_SDL_Window == NULL )
    {
        DEBUG_LOG( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        err = eError_SDL_Error;
    }
    else
    {
        //Get window surface
        m_SDL_Surface = SDL_GetWindowSurface( m_SDL_Window );

        if( m_SDL_Surface == NULL )
        {
            DEBUG_LOG( "Surface could not be fetched! SDL_Error: %s\n", SDL_GetError() );
            err = eError_SDL_Error;   
        }
    }

	return err;
}

// Update the window
eError SDLWindow::Update()
{
    eError err = eError_noErr;

    //Update the surface
    SDL_UpdateWindowSurface( m_SDL_Window );

    return err;
}

// Destroy the window
eError SDLWindow::Destroy()
{
	eError err = eError_noErr;

	//Deallocate surface
    SDL_FreeSurface( m_SDL_Surface );
    m_SDL_Surface = NULL;

    //Destroy window
    SDL_DestroyWindow( m_SDL_Window );
    m_SDL_Window = NULL;

	return err;
}