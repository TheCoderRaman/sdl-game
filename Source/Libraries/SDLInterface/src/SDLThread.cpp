//! \file SDLThread.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Wrapper for various SDL_Thread functions
//!	Found at https://wiki.libsdl.org/CategoryThread
#include "SDLThread.h"

#include "SDLTimer.h"

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

	// Sanity asserts
	DEBUG_ASSERT(m_threadFunc != nullptr);
	DEBUG_ASSERT(m_name != nullptr);
	DEBUG_ASSERT(m_sdl_thread == nullptr);

	m_sdl_thread = SDL_CreateThread(*m_threadFunc, m_name, data);

	// sanity check
	if (m_threadFunc == nullptr)
	{
		err |= eError::SDL_Fatal;
	}

	return err;
}

//========================================================
eError SDLInterface::Thread::Wait()
{
	eError err = eError::NoErr;

	// Sanity check on this
	DEBUG_ASSERT(m_sdl_thread != nullptr);

	// The return value of the thread
	int returnVal = 0;

	// Wait for the thread to finish
	// Possible timeout?
	SDL_WaitThread(m_sdl_thread, &returnVal);

	// Invalidate the thread pointer
	m_sdl_thread = nullptr;

	return (eError)returnVal;
}

//========================================================
eError SDLInterface::Thread::Detach()
{
	eError err = eError::NoErr;


	// Sanity check
	DEBUG_ASSERT(m_sdl_thread != nullptr);

#ifndef LINUX_BUILD
	// Detach the thread
	SDL_DetachThread(m_sdl_thread);
#else 
	// for some unknown and weirdo reason SDL_DetachThread fails to link here
	// on my ubuntu install. lo frikkin clue
	DEBUG_ASSERT(nullptr);
#endif

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

//========================================================
eError SDLInterface::Thread::DelayUntil(ms globaltime)
{
	eError err = eError::NoErr; 

	// Grab the current time
	ms currentTime = Timer::GetGlobalLifetime();

	// calculate the time until the specified time
	ms timeUntil = globaltime - currentTime;

	// if the time is positive
	if (timeUntil > 0)
	{
		// Call the SDL delay function
		err |= Delay(timeUntil);
	}
	// Otherwise we just want to return straight away
	//else

	return err;
}