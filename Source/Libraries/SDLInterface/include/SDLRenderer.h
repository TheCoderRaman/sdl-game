#ifndef _SDLRENDERER_H_
#define _SDLRENDERER_H_

// Includes
#include "error.h"

// Forward declares
class SDL_Renderer;
class SDLWindow;

// References for how to use SDL_Renderer can be found
// here : https://wiki.libsdl.org/CategoryRender

class SDLRenderer 
{
public:

	SDLRenderer();
	~SDLRenderer();

	// Create
	eError Create( SDLWindow* window );

	// Render
	eError Render();

	// Destroy
	eError Destroy();

private:

	// The actual SDL Renderer
	SDL_Renderer* myRenderer;
};

#endif //_SDLRENDERER_H_