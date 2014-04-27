//! \file SDLSurface.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! References for how to use SDL_Surface can be found
//! here : https://wiki.libsdl.org/SDL_Surface
#include "SDLSurface.h"

#include "eError.h"

//========================================================
SDLInterface::Surface::Surface()
: m_sdl_surface( nullptr )
{

}

//========================================================
SDLInterface::Surface::~Surface()
{

}

//========================================================
eError SDLInterface::Surface::Create()
{
	eError err = eError::NoErr;

	return err;
}

//========================================================
eError SDLInterface::Surface::Destroy()
{
	eError err = eError::NoErr;

	return err;
}