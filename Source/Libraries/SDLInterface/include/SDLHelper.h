//! \file SDLHelper.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for Helper.cpp
//!
#ifndef _SDLHELPER_H_
#define _SDLHELPER_H_


// Forward declare SDL structs
struct SDL_Renderer;
struct SDL_Window;
struct SDL_Surface;
struct SDL_Texture;

// Start the SDLInterface Namespace
namespace SDLInterface
{

	// Forward declares
	class Window;
	class Renderer;
	class Texture;
	class Surface;

	//! \brief Class to help with interrelation between other SDL classes
	//! This class will enable other SDLInterface classes to interact with their SDL components
	//! while also keeping a solid interface from that outside that does not confuse things
	class Helper
	{
	public:

		//! \brief Fetches the underlying SDL_Renderer from an Renderer
		static SDL_Renderer*	GetSDL_Renderer(Renderer* renderer);

		//! \brief Fetches the underlying SDL_Window from an Window
		static SDL_Window*		GetSDL_Window(Window* window);

		//! \brief Fetches the underlying SDL_Surface from an surface
		static SDL_Surface*		GetSDL_Surface(Surface* surface);

		//! \brief Fetches the underlying SDL_Texture from an Texture
		static SDL_Texture*		GetSDL_Texture(Texture* texture);
	};

}

#endif //_SDLHELPER_H_