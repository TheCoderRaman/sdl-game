//! \file SDLMutex.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for SDLMutex.cpp
//!	
#ifndef _SDLMUTEX_H_
#define _SDLMUTEX_H_

#include "types.h"

// Forward declares
class SDL_Mutex;

class SDLMutex
{
public:

	SDLMutex();
	~SDLMutex();

	eError Create();
	eError Destroy();

	void Lock();

	void Unlock();

private:
	
};

#endif _SDLMUTEX_H_