//! \file SDLRenderer.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for SDLRenderer.cpp
//! References for how to use SDL_Renderer can be found
//! here : https://wiki.libsdl.org/CategoryRender

#ifndef _SDLRENDERER_H_
#define _SDLRENDERER_H_

// Includes
#include "types.h"

// for friending
#include "SDLHelper.h"

// Forward declare SDL struct 
struct SDL_Renderer;

// Start the SDLInterface Namespace
namespace SDLInterface
{

	// Forward declare the window
	class SDLWindow;


	//! \brief the Renderer class
	//! functions as a wrapper for SDL_Renderer
	class SDLRenderer
	{
		friend class SDLHelper; // Allow SDLHelper to access my members
	public:

		//! \brief Constructor
		SDLRenderer();

		//! \brief Destructor
		~SDLRenderer();

		//! \brief Create the renderer from a window
		eError Create(SDLWindow* window);

		//! \brief render using the renderer
		eError Render();

		//! \brief destroy the renderer
		eError Destroy();

	private:

		//! \brief The actual SDL Renderer
		SDL_Renderer* m_SDL_Renderer;
	};

}

#endif //_SDLRENDERER_H_