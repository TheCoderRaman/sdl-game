//! \file SDLMutex.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Wrapper for various SDL_mutex functions
//!	Found at https://wiki.libsdl.org/CategoryMutex
#include "SDLMutex.h"

#include "debug.h"
#include "eError.h"

#include "SDL.h"

SDLMutex::SDLMutex()
: my_sdl_mutex( nullptr )
{

}

SDLMutex::~SDLMutex()
{
	// Sanity check that destroy has been called
	DEBUG_ASSERT(my_sdl_mutex == nullptr);
}

eError SDLMutex::Create()
{
	DEBUG_ASSERT(my_sdl_mutex == nullptr);

	my_sdl_mutex = SDL_CreateMutex();

	return eError::noErr;
}

eError SDLMutex::Destroy()
{
	DEBUG_ASSERT(my_sdl_mutex != nullptr);

	SDL_DestroyMutex(my_sdl_mutex);

	return eError::noErr;
}

eError SDLMutex::Lock()
{
	DEBUG_ASSERT(my_sdl_mutex != nullptr);

	SDL_LockMutex(my_sdl_mutex);

	return eError::noErr;
}

eError SDLMutex::Unlock()
{
	DEBUG_ASSERT(my_sdl_mutex != nullptr);

	SDL_UnlockMutex(my_sdl_mutex);

	return eError::noErr;
}

SDLAutoMutex::SDLAutoMutex(SDLMutex* theMutex)
: m_myMutex( theMutex )
{
	DEBUG_ASSERT(theMutex != nullptr);

	eError err = m_myMutex->Lock();

	DEBUG_ASSERT(!ERROR_HAS_TYPE_FATAL(err));
}

SDLAutoMutex::~SDLAutoMutex()
{
	eError err = m_myMutex->Unlock();

	DEBUG_ASSERT(!ERROR_HAS_TYPE_FATAL(err));
}