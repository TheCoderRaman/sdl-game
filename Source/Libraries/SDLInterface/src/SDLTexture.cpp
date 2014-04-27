//! \file SDLTexture.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! References for how to use SDL_Texture can be found
//! here : https://wiki.libsdl.org/SDL_Texture
#include "SDLTexture.h"

#include "eError.h"

//========================================================
SDLInterface::Texture::Texture()
: m_sdl_texture(nullptr)
{

}

//========================================================
SDLInterface::Texture::~Texture()
{

}

//========================================================
eError SDLInterface::Texture::Create()
{
	eError err = eError::NoErr;

	return err;
}

//========================================================
eError SDLInterface::Texture::Create(Surface* surface)
{
	eError err = eError::NoErr;

	return err;
}

//========================================================
eError SDLInterface::Texture::Destroy()
{
	eError err = eError::NoErr;

	return err;
}