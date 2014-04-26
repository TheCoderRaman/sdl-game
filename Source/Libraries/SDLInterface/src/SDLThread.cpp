//! \file Thread.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Wrapper for various SDL_Thread functions
//!	Found at https://wiki.libsdl.org/CategoryThread
#include "SDLThread.h"

#include "eError.h"
#include "debug.h"

#include "SDL.h"

//========================================================
SDLInterface::Thread::Thread()
: m_sdl_thread(nullptr)
, m_threadFunc(nullptr)
, m_name("unnamed")
{

}

//========================================================
SDLInterface::Thread::Thread(const char* name, ThreadFunction func)
: m_sdl_thread(nullptr)
, m_threadFunc(func)
, m_name(name)
{

}

SDLInterface::Thread::~Thread()
{
	// Detach or Wait must be called before allowing an Thread to destruct
	DEBUG_ASSERT(m_sdl_thread == nullptr);
}

//========================================================
eError SDLInterface::Thread::Spawn(void* data)
{
	eError err = eError::NoErr;
	
	//TODO: Use error right

	// Sanity asserts
	DEBUG_ASSERT(m_threadFunc != nullptr);
	DEBUG_ASSERT(m_name != nullptr);
	DEBUG_ASSERT(m_sdl_thread == nullptr);

	m_sdl_thread = SDL_CreateThread(*m_threadFunc, m_name, data);

	return err;
}

//========================================================
eError SDLInterface::Thread::Wait()
{
	eError err = eError::NoErr;

	//TODO: Use error right

	// Sanity check on this
	DEBUG_ASSERT(m_sdl_thread != nullptr);

	// The return value of the thread
	int returnVal = 0;

	// Wait for the thread to finish
	SDL_WaitThread(m_sdl_thread, &returnVal);

	// Invalidate the thread pointer
	m_sdl_thread = nullptr;

	return (eError)returnVal;
}

//========================================================
eError SDLInterface::Thread::Detach()
{
	eError err = eError::NoErr;

	//TODO: Use error right

	// Sanity check
	DEBUG_ASSERT(m_sdl_thread != nullptr);

	// Detach the thre
	SDL_DetachThread(m_sdl_thread);

	//invalidate the thread pointer
	m_sdl_thread = nullptr;

	return err;
}

//========================================================
eError SDLInterface::Thread::Delay(ms time)
{
	// Call the SDL delay function
	SDL_Delay(time);

	return eError::NoErr;
}