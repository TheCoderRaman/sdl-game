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

//========================================================
SDLMutex::SDLMutex()
: my_sdl_mutex( nullptr )
{

}

//========================================================
SDLMutex::~SDLMutex()
{
	// Sanity check that destroy has been called
	DEBUG_ASSERT(my_sdl_mutex == nullptr);
}

//========================================================
eError SDLMutex::Create()
{
	DEBUG_ASSERT(my_sdl_mutex == nullptr);

	my_sdl_mutex = SDL_CreateMutex();

	return eError::noErr;
}

//========================================================
eError SDLMutex::Destroy()
{
	DEBUG_ASSERT(my_sdl_mutex != nullptr);

	SDL_DestroyMutex(my_sdl_mutex);
	my_sdl_mutex = nullptr;

	return eError::noErr;
}

//========================================================
eError SDLMutex::Lock()
{
	DEBUG_ASSERT(my_sdl_mutex != nullptr);

	SDL_LockMutex(my_sdl_mutex);

	return eError::noErr;
}

//========================================================
eError SDLMutex::Unlock()
{
	DEBUG_ASSERT(my_sdl_mutex != nullptr);

	SDL_UnlockMutex(my_sdl_mutex);

	return eError::noErr;
}

//========================================================
SDLSemaphore::SDLSemaphore()
: m_mySem(nullptr)
{

}

//========================================================
SDLSemaphore::~SDLSemaphore()
{
	// Sanity check that destroy has been called
	DEBUG_ASSERT(m_mySem == nullptr);
}

//========================================================
eError SDLSemaphore::Create()
{
	DEBUG_ASSERT(m_mySem == nullptr);

	m_mySem = SDL_CreateSemaphore(0);

	return eError::noErr;
}

//========================================================
eError SDLSemaphore::Destroy()
{
	DEBUG_ASSERT(m_mySem != nullptr);

	SDL_DestroySemaphore(m_mySem);
	m_mySem = nullptr;

	return eError::noErr;
}

//========================================================
eError SDLSemaphore::Post()
{
	DEBUG_ASSERT(m_mySem != nullptr);

	SDL_SemPost(m_mySem);

	return eError::noErr;
}

//========================================================
eError SDLSemaphore::Wait()
{
	DEBUG_ASSERT(m_mySem != nullptr);

	SDL_SemWait(m_mySem);

	return eError::noErr;
}
