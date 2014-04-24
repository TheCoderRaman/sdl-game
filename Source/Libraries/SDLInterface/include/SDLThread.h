//! \file SDLThread.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for SDLThread.cpp
//!	
#ifndef _SDLTHREAD_H_
#define _SDLTHREAD_H_

// Includes
#include "types.h"

// Forward declarations for SDL stuff
struct SDL_Thread;
typedef int (* SDL_ThreadFunction) (void *data);

// Typedef for the function required to launch a thread
typedef int(*ThreadFunction)(void*);

//! brief the SDLThread namespace
namespace SDLThread
{
	//! \brief container for all thread data
	struct Thread
	{
		//! \brief tiny constructor to ensure everything is set to default
		Thread()
		: m_sdl_thread( nullptr )
		, name("unnamed")
		{}

		//! \brief the underlying SDL thread object
		SDL_Thread* m_sdl_thread;

		//! \brief the thread name
		const char* name;
	};

	//! \brief Spawn a thread with \a name and \a func with \a data
	//! \warning this Thread will hang around untill Wait or Detach are called on it
	eError SpawnThread(Thread& newThread, ThreadFunction func, void* data);

	//! \brief Wait for a thread to finish
	//! \warning this will not return until the thread returns
	eError WaitForThread(Thread& thread, int* returnVal);

	//! \brief Detach a thread
	//! This detaches the thread, telling it that it does not need to hang around
	//! until Wait is called.
	//! \warning This thread is now completely detached so no return code can be recieved
	//! \warning This Thread object is now invalid and cannot have Wait or Detach called on it
	eError DetachThread(Thread& thread);

}


#endif //_SDLTHREAD_H_