//! \file SDLRenderer.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for Renderer.cpp
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
	class Window;


	//! \brief the Renderer class
	//! functions as a wrapper for SDL_Renderer
	class Renderer
	{
		friend class Helper; // Allow Helper to access my members
	public:

		//! \brief Constructor
		Renderer();

		//! \brief Destructor
		~Renderer();

		//! \brief Create the renderer from a window
		eError Create(Window* window);

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