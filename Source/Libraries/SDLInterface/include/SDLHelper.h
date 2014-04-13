//! \file SDLHelper.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for SDLHelper.cpp
//!
#ifndef _SDLHELPER_H_
#define _SDLHELPER_H_

// Forward declares
class SDLWindow;
class SDLRenderer;

struct SDL_Renderer;
struct SDL_Window;
struct SDL_Surface;

//! \brief Class to help with interrelation between other SDL classes
//! This class will enable other SDLInterface classes to interact with their SDL components
//! while also keeping a solid interface from that outside that does not confuse things
class SDLHelper
{
public:

	static SDL_Renderer*	GetSDL_Renderer( SDLRenderer* renderer );
	static SDL_Window*		GetSDL_Window( SDLWindow* window );
	static SDL_Surface*		GetSDL_Surface( SDLWindow* window );


};

#endif //_SDLHELPER_H_