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

// for the rectangles
#include "SDLRect.h"

// Forward declare SDL struct 
struct SDL_Renderer;

// Start the SDLInterface Namespace
namespace SDLInterface
{

	// Forward declare the window
	class Window;

	// Forward declare the Texture
	class Texture;


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
		eError RenderStart();

		//! \brief render a texture
		eError RenderTexture(Texture* tex, const Rect& src, const Rect& dest);

		//! \brief render a texture
		eError RenderRectangle(const Rect& src, int r, int g, int b, int a, bool fill = true);

		//! \brief render using the renderer
		eError RenderEnd();

		//! \brief destroy the renderer
		eError Destroy();

	private:

		//! \brief The actual SDL Renderer
		SDL_Renderer* m_SDL_Renderer;

		//! \brief boolean to check if we're rendering
		bool m_bRendering;
	};

}

#endif //_SDLRENDERER_H_