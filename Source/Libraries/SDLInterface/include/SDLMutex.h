//! \file SDLMutex.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for SDLMutex.cpp
//!	
#ifndef _SDLMUTEX_H_
#define _SDLMUTEX_H_

// For eError
#include "types.h"

// Forward declares
struct SDL_mutex;

//! \brief a Mutex class
//! A mutex is used to allow a function to stop progress until some other concurrent progress is finished
//! In short: a mutex prevents concurrent access of data
//! ie. Thread1 locks the mutex, does some stuff. Thread2 meanwhile needs to do things but when 
//! it tries to lock the mutex, it must wait untill Thread1 has unlocked and let it continue.
class SDLMutex
{
public:

	// Constructor and destructor
	SDLMutex();
	~SDLMutex();

	//! \brief Create the mutex (must be called)
	eError Create();

	//! \brief Destroy the mutex (must be called before destruction)
	eError Destroy();

	//! \brief Lock the mutex
	//! \warning will not return untill mutex has been locked, ie. all other locks have unlocked
	eError Lock();

	//! \brief Unlock the mutex
	//! MUST be called if Lock() was called
	eError Unlock();

private:
	
	//! \brief the sdl mutex
	SDL_mutex* my_sdl_mutex;
};

struct SDL_semaphore;

class SDLSemaphore
{
public:

	// Constructor and destructor
	SDLSemaphore();
	~SDLSemaphore();

	//! \brief Create the semaphore (must be called)
	eError Create();

	//! \brief Destroy the semaphore (must be called before destruction)
	eError Destroy();

	//! \brief Post the semaphore
	eError Post();

	//! \brief Waits for the semaphore
	//! \warning will block until Post is called
	eError Wait();

private:

	//! \brief the internal SDL semaphore
	SDL_semaphore* m_mySem;

};

#endif _SDLMUTEX_H_