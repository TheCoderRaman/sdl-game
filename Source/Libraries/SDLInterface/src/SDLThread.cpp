//! \file SDLThread.cpp
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
eError SDLThread::SpawnThread(SDLThread::Thread& newThread, ThreadFunction func, void* data)
{
	eError err = eError::NoErr;
	
	//TODO: Use error right

	DEBUG_ASSERT(newThread.m_sdl_thread == nullptr);
	newThread.m_sdl_thread = SDL_CreateThread( *func, newThread.name, data);	

	return err;
}

//========================================================
eError SDLThread::WaitForThread(SDLThread::Thread& thread)
{
	eError err = eError::NoErr;

	//TODO: Use error right
	int returnVal = 0;

	DEBUG_ASSERT(thread.m_sdl_thread != nullptr);
	SDL_WaitThread(thread.m_sdl_thread, &returnVal);

	return (eError)returnVal;
}

//========================================================
eError SDLThread::DetachThread(SDLThread::Thread& thread)
{
	eError err = eError::NoErr;

	//TODO: Use error right

	DEBUG_ASSERT(thread.m_sdl_thread != nullptr);
	SDL_DetachThread(thread.m_sdl_thread);

	//invalidate the thread pointer
	thread.m_sdl_thread = nullptr;

	return err;
}

//========================================================
eError SDLThread::Delay(ms time)
{
	// Call the SDL delay function
	SDL_Delay(time);

	return eError::NoErr;
}