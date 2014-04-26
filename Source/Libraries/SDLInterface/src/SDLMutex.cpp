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
SDLInterface::SDLMutex::SDLMutex()
: my_sdl_mutex( nullptr )
{

}

//========================================================
SDLInterface::SDLMutex::~SDLMutex()
{
	// Sanity check that destroy has been called
	DEBUG_ASSERT(my_sdl_mutex == nullptr);
}

//========================================================
eError SDLInterface::SDLMutex::Create()
{
	DEBUG_ASSERT(my_sdl_mutex == nullptr);

	my_sdl_mutex = SDL_CreateMutex();

	return eError::NoErr;
}

//========================================================
eError SDLInterface::SDLMutex::Destroy()
{
	DEBUG_ASSERT(my_sdl_mutex != nullptr);

	SDL_DestroyMutex(my_sdl_mutex);
	my_sdl_mutex = nullptr;

	return eError::NoErr;
}

//========================================================
eError SDLInterface::SDLMutex::Lock()
{
	DEBUG_ASSERT(my_sdl_mutex != nullptr);

	SDL_LockMutex(my_sdl_mutex);

	return eError::NoErr;
}

//========================================================
eError SDLInterface::SDLMutex::Unlock()
{
	DEBUG_ASSERT(my_sdl_mutex != nullptr);

	SDL_UnlockMutex(my_sdl_mutex);

	return eError::NoErr;
}

//========================================================
SDLInterface::SDLSemaphore::SDLSemaphore()
: m_mySem(nullptr)
{

}

//========================================================
SDLInterface::SDLSemaphore::~SDLSemaphore()
{
	// Sanity check that destroy has been called
	DEBUG_ASSERT(m_mySem == nullptr);
}

//========================================================
eError SDLInterface::SDLSemaphore::Create()
{
	DEBUG_ASSERT(m_mySem == nullptr);

	m_mySem = SDL_CreateSemaphore(0);

	return eError::NoErr;
}

//========================================================
eError SDLInterface::SDLSemaphore::Destroy()
{
	DEBUG_ASSERT(m_mySem != nullptr);

	SDL_DestroySemaphore(m_mySem);
	m_mySem = nullptr;

	return eError::NoErr;
}

//========================================================
eError SDLInterface::SDLSemaphore::Post()
{
	DEBUG_ASSERT(m_mySem != nullptr);

	SDL_SemPost(m_mySem);

	return eError::NoErr;
}

//========================================================
eError SDLInterface::SDLSemaphore::Wait()
{
	DEBUG_ASSERT(m_mySem != nullptr);

	SDL_SemWait(m_mySem);

	return eError::NoErr;
}
