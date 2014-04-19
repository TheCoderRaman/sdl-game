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
#include "fnQueue.h"

// Forward declarations for SDL stuff
class SDL_Thread;
class SDL_ThreadFunction;

// Typedef for the function required to launch a thread
typedef int(*ThreadFunction)(void*);

//! brief the SDLThread namespace
namespace SDLThread
{
	//! \brief container for all thread data
	struct Thread
	{
		//! \brief the underlying SDL thread object
		SDL_Thread* m_sdl_thread;

		//! \brief the thread name
		const char* name;
	};

	//! \brief Spawn a thread with \a name and \a func with \a data
	Thread SpawnThread(const char* name, ThreadFunction func, void* data);

	//! \brief Wait for a thread to finish
	eError WaitForThread(Thread& thread, int* returnVal);

	//! \brief the type for the main thread queue
	typedef fnQueue< eError(void) > TMainThreadFnQueue;

	//! \brief Set the main thread queue object
	eError SetMainThreadQueue( TMainThreadFnQueue* theQueue);

	//! \brief Run a function on the main thread Syncronously with return value
	//! This function will not return untill the function on the main thread is complete
	eError RunOnMainThread_Sync( TMainThreadFnQueue::TFunction, eError& returnVal);

	//! \brief Run a function on the main thread ASyncronously
	//! This function will return instantly, with no wait, and give any error code if there was an issue
	eError RunOnMainThread_ASync(TMainThreadFnQueue::TFunction );

	 
}


#endif //_SDLTHREAD_H_