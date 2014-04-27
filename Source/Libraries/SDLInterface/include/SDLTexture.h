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

#include "types.h" // For eError

#include "SDLSurface.h" // for SDLInterface::Surface

// Forward declare the SDL_Texture type from SDL
struct SDL_Texture;

// Start the SDLInterface Namespace
namespace SDLInterface
{
	//! \brief wrapper class for SDL_Texture
	class Texture
	{
	public:

		//! \brief default constructor
		Texture();

		//! \brief default destructor
		~Texture();

		//! \brief Create the texture
		eError Create();

		//! \brief Create the texture from a surface
		eError Create(Surface* surface);

		//! \brief destroy the surface
		eError Destroy();

	private:

		//! \brief the internal SDL_Texture
		SDL_Texture* m_sdl_texture;

	};
}

#endif //_SDLTEXTURE_H_