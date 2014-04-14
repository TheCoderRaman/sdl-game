//! \file SDLRenderer.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for SDLRenderer.cpp
//!
#ifndef _SDLRENDERER_H_
#define _SDLRENDERER_H_

// Includes
#include "eError.h"

// for friending
#include "SDLHelper.h"

// Forward declares
struct SDL_Renderer;
class SDLWindow;

// References for how to use SDL_Renderer can be found
// here : https://wiki.libsdl.org/CategoryRender

class SDLRenderer 
{
	friend class SDLHelper;
public:

	//! \brief Constructor
	SDLRenderer();

	//! \brief Destructor
	~SDLRenderer();

	// Create
	eError Create( SDLWindow* window );

	// Render
	eError Render();

	// Destroy
	eError Destroy();

private:

	// The actual SDL Renderer
	SDL_Renderer* m_SDL_Renderer;
};

#endif //_SDLRENDERER_H_