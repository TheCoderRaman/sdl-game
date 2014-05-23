//! \file SDLTexture.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for SDLTexture.cpp
//! References for how to use SDL_Texture can be found
//! here : https://wiki.libsdl.org/SDL_Texture
#ifndef _SDLTEXTURE_H_
#define _SDLTEXTURE_H_

#include "SDLCommon.h"

#include "SDLHelper.h" // for friending

// Forward declare the SDL_Texture type from SDL
struct SDL_Texture;

// Start the SDLInterface Namespace
namespace SDLInterface
{
	class Surface;
	class Renderer;

	//! \brief wrapper class for SDL_Texture
	class Texture
	{
		//! Friends with Helper to let it access it's internals
		friend class Helper;
	public:

		//! \brief default constructor
		Texture();

		//! \brief default destructor
		~Texture();

		//! \brief Create the texture
		//! \warning Not implemented, not sure how to do this properly
		Error Create();

		//! \brief Create the texture from a file and a renderer
		Error Create(Renderer* renderer, const char* file);

		//! \brief Create the texture from a surface and a renderer
		Error Create(Renderer* renderer, Surface* surface);

		//! \brief destroy the surface
		Error Destroy();

	private:

		//! \brief the internal SDL_Texture
		SDL_Texture* m_sdl_texture;

	};
}

#endif //_SDLTEXTURE_H_