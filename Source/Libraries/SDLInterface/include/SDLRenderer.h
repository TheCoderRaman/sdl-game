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

#include "SDLCommon.h"

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

	//! \brief Render scale struct to describe engine -> SDL position translations
	struct RenderScale
	{
		//! \brief default constuctor
		RenderScale()
		{
			factor.x = 1.0f;
			factor.y = 1.0f;
			offset.x = 0.0f;
			offset.y = 0.0f;
		}

		struct
		{	
			float x, y;
		} factor;

		struct
		{
			float x, y;
		} offset;
	};

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
		Error Create(Window* window);

		//! \brief render using the renderer
		Error RenderStart();

		//! \brief render a texture
		Error RenderTexture(Texture* tex, const Rect& src, const Rect& dest, float rotation = 0.0f, const Point& centerRot = Point(), int flipValue = 0);

		//! \brief render a Rectangle
		Error RenderRectangle(const Rect& src, int r, int g, int b, int a, bool fill = true);

		//! \brief render a line
		Error RenderLine(const Point& start, const Point& end, int r, int g, int b, int a);

		//! \brief render using the renderer
		Error RenderEnd();

		//! \brief destroy the renderer
		Error Destroy();
		
		//! \brief Set the render factor 
		inline void SetRenderFactors(RenderScale factors)
		{
			m_renderScale = factors;
		}

	private:

		//! \brief The actual SDL Renderer
		SDL_Renderer* m_SDL_Renderer;

		//! \brief boolean to check if we're rendering
		bool m_bRendering;

		//! \brief the renderer scale and offset 
		RenderScale m_renderScale;
	};

}

#endif //_SDLRENDERER_H_