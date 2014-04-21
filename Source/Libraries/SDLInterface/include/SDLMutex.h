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


//! \brief Little helper class to automatically unlock a mutext on destruction
//! \warning do NOT give this a mutex that may have been destroyed by the end of this objects lifetime
class SDLAutoMutex
{
public:

	//! \brief Create the automutex object. Will lock /a theMutex 
	SDLAutoMutex(SDLMutex* theMutex);

	//! \brief This will unlock \a m_myMutex
	~SDLAutoMutex();

private:

	// Private - must be constructed with mutex
	SDLAutoMutex();

	//! \brief the mutex to automatically lock/unlock
	SDLMutex* m_myMutex;
};

#endif _SDLMUTEX_H_