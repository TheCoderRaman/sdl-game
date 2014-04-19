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

SDLThread::TMainThreadFnQueue* s_MainThreadQueue = nullptr;

eError SDLThread::SetMainThreadQueue(TMainThreadFnQueue* theQueue)
{
	eError err = eError::noErr;

	// Sanity check on the queue already being null
	if (s_MainThreadQueue == nullptr)
	{
		s_MainThreadQueue = theQueue;
	}
	else
	{
		// Possibly use a more specific error here
		// Not fatal however
		err = eError::Catagory_SDL;
	}

	return err;
}

//! \brief Spawn a thread with \a name and \a func with \a data
//! \warning this Thread will hang around untill Wait or Detach are called on it
eError SDLThread::SpawnThread(SDLThread::Thread& newThread, ThreadFunction func, void* data)
{
	eError err = eError::noErr;
	
	//TODO: Use error right

	DEBUG_ASSERT(newThread.m_sdl_thread == nullptr);
	newThread.m_sdl_thread = SDL_CreateThread( *func, newThread.name, data);	

	return err;
}

//! \brief Wait for a thread to finish
//! \warning this will not return until the thread returns
eError SDLThread::WaitForThread(SDLThread::Thread& thread, int* returnVal)
{
	eError err = eError::noErr;

	//TODO: Use error right

	DEBUG_ASSERT(thread.m_sdl_thread != nullptr);
	SDL_WaitThread(thread.m_sdl_thread, returnVal);

	return err;
}

//! \brief Detach a thread
//! This detaches the thread, telling it that it does not need to hang around
//! until Wait is called.
//! \warning This thread is now completely detached so no return code can be recieved
//! \warning This Thread object is now invalid and cannot have Wait or Detach called on it
eError SDLThread::DetachThread(SDLThread::Thread& thread)
{
	eError err = eError::noErr;

	//TODO: Use error right

	DEBUG_ASSERT(thread.m_sdl_thread != nullptr);
	SDL_DetachThread(thread.m_sdl_thread);

	//invalidate the thread pointer
	thread.m_sdl_thread = nullptr;

	return err;
}