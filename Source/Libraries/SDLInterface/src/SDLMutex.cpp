//! \file SDLMutex.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Wrapper for various SDL_mutex functions
//!	Found at https://wiki.libsdl.org/CategoryMutex
#include "SDLMutex.h"

#include "debug.h"

SDLMutex::SDLMutex()
: my_sdl_mutex( nullptr )
{

}

SDLMutex::~SDLMutex()
{
	// Sanity check that destroy has been called
	DEBUG_ASSERT(my_sdl_mutex == nullptr);
}