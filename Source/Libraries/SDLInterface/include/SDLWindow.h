#pragma once

// Includes
#include "types.h"

// Forward declares
struct SDL_Window;
struct SDL_Surface;

class SDLWindow
{
public:

	SDLWindow();
	~SDLWindow();

	eError Create();

	eError Update();

	eError Destroy();

private:

	SDL_Window* 		m_SDL_Window;
	SDL_Surface* 		m_SDL_Surface;

};