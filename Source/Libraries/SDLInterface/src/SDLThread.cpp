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
SDLThread::SDLThread()
: m_sdl_thread(nullptr)
, m_threadFunc(nullptr)
, m_name("unnamed")
{

}

//========================================================
SDLThread::SDLThread(const char* name, ThreadFunction func)
: m_sdl_thread(nullptr)
, m_threadFunc(func)
, m_name(name)
{

}

SDLThread::~SDLThread()
{
	// Detach or Wait must be called before allowing an SDLThread to destruct
	DEBUG_ASSERT(m_sdl_thread == nullptr);
}

//========================================================
eError SDLThread::Spawn(void* data)
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
eError SDLThread::Wait()
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
eError SDLThread::Detach()
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
eError SDLThread::Delay(ms time)
{
	// Call the SDL delay function
	SDL_Delay(time);

	return eError::NoErr;
}