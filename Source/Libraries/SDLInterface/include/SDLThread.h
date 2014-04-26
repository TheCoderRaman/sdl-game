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

//! \brief  Forward declarations for SDL stuff
struct SDL_Thread;

//! \brief type of thread function from SDL
typedef int (* SDL_ThreadFunction) (void *data);

// Start the SDLInterface Namespace
namespace SDLInterface
{

	//! \brief the SDLThread class
	class SDLThread
	{
	public:
		//! \brief Typedef for the function required to launch a thread
		typedef SDL_ThreadFunction ThreadFunction;

		//! \brief tiny constructor to ensure everything is set to default
		SDLThread();

		//! \brief destructor
		~SDLThread();

		//! \brief second constructor with name
		SDLThread(const char* name, ThreadFunction func);

		//! \brief Spawn a thread with \a name and \a func with \a data
		//! \warning this Thread will hang around untill Wait or Detach are called on it
		eError Spawn(void* data);

		//! \brief Wait for a thread to finish
		//! \warning this will not return until the thread returns
		eError Wait();

		//! \brief Detach a thread
		//! This detaches the thread, telling it that it does not need to hang around
		//! until Wait is called.
		//! \warning This thread is now completely detached so no return code can be recieved
		//! \warning This Thread object is now invalid and cannot have Wait or Detach called on it
		eError Detach();

		//! \brief thread time delay
		static eError Delay(ms time);

	private:

		//! \brief the underlying SDL thread object
		SDL_Thread* m_sdl_thread;

		//! \brief the thread function to use
		ThreadFunction m_threadFunc;

		//! \brief the thread name
		const char* m_name;

	};

}

#endif //_SDLTHREAD_H_