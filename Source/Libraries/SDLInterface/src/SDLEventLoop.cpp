//! \file SDLEventLoop.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Description
//! 
#include "SDLEventLoop.h"

#include "SDL.h"

#include "debug.h"
#include "types.h"
#include "SDLError.h"

#include "SDLMutex.h"
#include "SDLEventHandling.h"

#include <atomic>

//! \brief the custom function event type
Uint32 s_iCustomFunctionEventType = 0;

//! \brief boolean to check if we're currently event handling
THREAD_LOCAL bool s_isCurrentlyEventHandling(false);

//! \brief param to check if it is safe to quit
std::atomic<bool> s_bEventLoopEnding(false);

//! \brief member to show that the eventloop is quitting
std::atomic<bool> s_bEventLoopQuitRequested(false);

//! \brief parameter to see if the eventloop is running
std::atomic<bool> s_bEventLoopRunning(false);

//========================================================
bool SDLInterface::EventLoop::IsLoopEnding()
{
	return s_bEventLoopEnding;
}

//========================================================
void SDLInterface::EventLoop::EndLoop()
{
	s_bEventLoopEnding = true;
}

//========================================================
bool SDLInterface::EventLoop::QuitHasBeenRequested()
{
	return s_bEventLoopQuitRequested;
}

//========================================================
void SDLInterface::EventLoop::RequestQuit()
{
	s_bEventLoopQuitRequested = true;
}

//========================================================
SDLInterface::Error SDLInterface::EventLoop::Create()
{
	Error err = Error::NoErr;

	// Register the custom event
	if (s_iCustomFunctionEventType == 0)
	{
		s_iCustomFunctionEventType = SDL_RegisterEvents(1);
	}
	else
	{
		err |= Error::Eventloop_double_create;
		DEBUG_LOG("ERROR Possible EventLoop::Create called twice?")
	}

	return err;
}

//========================================================
SDLInterface::Error SDLInterface::EventLoop::Destroy()
{
	Error err = Error::NoErr;

	return err;
}

//========================================================
SDLInterface::Error SDLInterface::EventLoop::DoLoop()
{
	Error err = Error::NoErr;

	//Event handler
    SDL_Event event;

	s_bEventLoopRunning = true;

	// Handle events on queue
	// End if there's a fatal error, or we've been told it's safe to quit
	while (!(SDL_ERROR_HAS_TYPE_FATAL(err) || IsLoopEnding()))
    {
		// Wait for an event with a timout of 10
		// timeout ensures we can quit
		const int ret = SDL_WaitEventTimeout( &event, 10 );

		// Handle the event
		if (ret > 0)
			err |= HandleEvent(&event);
    }

	SDL_REMOVE_ERR(err, Error::QuitRequest);

    if ( err != Error::NoErr )
    	DEBUG_LOG("DoLoop Dropped out with Error %i",err);

	s_bEventLoopRunning = false;

    return err;
}

//========================================================
SDLInterface::Error SDLInterface::EventLoop::HandleEvent(SDL_Event *event)
{
	Error err = Error::NoErr;

	// Set we're currently event handling
	s_isCurrentlyEventHandling = true;

	// switch through all the event types
	switch (event->type)
	{
		case SDL_QUIT:
			DEBUG_LOG("SDL_QUIT recieved");
			RequestQuit();
			break;

		default:
			if (event->type == s_iCustomFunctionEventType)
			{
				err |= HandleCustomFunctionEvent(event);
			}
			else
			{
				EventHandling::HandleEvent(event);
			}
			break;
	}

	// Turn off current event handline
	s_isCurrentlyEventHandling = false;

	return err;
}

//========================================================
SDLInterface::Error SDLInterface::EventLoop::HandleCustomFunctionEvent(SDL_Event *event)
{
	Error err = Error::NoErr;

	// Grab  the function
	TMainThreadFunction* function = static_cast<TMainThreadFunction*>(event->user.data1);

	// Call the function
	err |= function->operator()();

	// delete the function ( it was newed in PostCustomFunctionEvent )
	delete function;

	return err;
}

//========================================================
SDLInterface::Error SDLInterface::EventLoop::PostCustomFunctionEvent(TMainThreadFunction& func)
{
	Error err = Error::NoErr;

	// NEW the function, to be deleted after the function is called
	// This is because whatever function was passed in may be out of scope by the time it gets called
	TMainThreadFunction* tempFunc = new TMainThreadFunction(func);

	// Create a custom event
	SDL_Event customEvent;
	SDL_zero(customEvent);

	// Set the custom event type and data
	customEvent.type = s_iCustomFunctionEventType;
	customEvent.user.code = 0; /* dunno */
	customEvent.user.data1 = tempFunc;
	customEvent.user.data2 = 0; /* anything else? */

	// push the event into the SDL event queue
	SDL_PushEvent(&customEvent);

	return err;
}

//========================================================
SDLInterface::Error SDLInterface::EventLoop::RunOnMainThread_Sync(Error& returnVal, TMainThreadFunction func)
{
	Error err = Error::NoErr;

	// We must be running at this point
	// Any functions that call into here before or after we're running the event loop
	// expose serious issues in call order
	DEBUG_ASSERT(s_bEventLoopRunning);

	// s_isCurrentlyEventHandling is thread local
	// That means if this is true then we're on the main thread AND we're alread handling an event
	// This means we may as well just call the function to prevent deadlocks
	if ( s_isCurrentlyEventHandling )
	{
		returnVal = func();
	}
	else
	{
		// Create a temporary semaphore
		Semaphore* tempSem = new Semaphore();
		tempSem->Create();

		// Create a new temporary function that will post the semaphore and grab the return value
		TMainThreadFunction newTempFunc = [&]()->Error {

			Error err = Error::NoErr;

			// Call the custom function and grab it's return value
			returnVal |= func();

			// Post the semaphore to show it has finished
			err |= tempSem->Post();
			
			return err;
		};

		// run it async for now until semaphore is implemented
		err |= PostCustomFunctionEvent(newTempFunc);

		// Wait for the semaphore to be posted
		tempSem->Wait();

		// Destroy the temporary semaphore
		tempSem->Destroy();
		delete tempSem;
	}

	return err;
}

//========================================================
SDLInterface::Error SDLInterface::EventLoop::RunOnMainThread_ASync(TMainThreadFunction func)
{
	Error err = Error::NoErr;

	// Post the custom function event
	err |= PostCustomFunctionEvent(func);

	return err;
}